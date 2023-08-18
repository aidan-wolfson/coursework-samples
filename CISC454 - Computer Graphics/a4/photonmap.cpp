// photonmap.cpp


#include <cstdlib>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <chrono>
#include "headers.h"
#include "photonmap.h"
#include "drawSegs.h"
#include "scene.h"
#include "main.h"
#include "priority.h"
#include "priority.cpp"		// necessary to show implemenation to compiler



#define GREY_COLOUR vec3( 0.6, 0.6, 0.6 )



// Trace lots of rays outward in random directions from each light.
// Then build the KD tree.


void PhotonMap::populate( Scene *scene )

{
  clear();

  // Collect the photons

  // YOUR CODE HERE
  //
  // Call forwardTraceRay() for lots of directions around each point
  // light.  Use randomDir() for the directions.
    
  for (int lightIndex = 0; lightIndex < scene->lights.size(); lightIndex++) {
      // iterate over all point lights in the scene
      for (int j = 0; j < PHOTONS_PER_LIGHT; j++) {
          // for each light, send out a bunch of rays 
          vec3 randDir = randomDir();
          forwardTraceRay(scene->lights[lightIndex]->position, randDir, vec3(1,1,1), lightIndex, -1, scene, false, 0);
      }
  }


  // Build the KD tree

  if (photons.size() > 0) {
    tree = new KDTree();
    tree->buildFromPhotons( photons, c000, c111 ); // also computes bounding box and stores in c000, c111
  }

  cout << "KD tree built.  " << photons.size() << " photons captured." << endl;
}



// Pick a uniform random direction


vec3 PhotonMap::randomDir() 

{
  // YOUR CODE HERE
  //
  // Generate a *uniform* random direction
    

   // vec3 dir = (0, 0, 0); // initializing

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_real_distribution<float> uniform01(0.0, 1.0);

    /*
    float x = rand();
    float y = rand();
    float z = rand();
    */
    float theta = 2 * M_PI * uniform01(generator);
    float phi = acos(1 - 2 * uniform01(generator));
    float x = sin(phi) * cos(theta);
    float y = sin(phi) * sin(theta);
    float z = cos(phi);
    vec3 dir = vec3(x, y, z);
    dir = dir.normalize();
    
    
    return dir;
    



  
  //return vec3( 1, 0, 0 );  // remove this once your code works
}



// Trace a ray from the light


void PhotonMap::forwardTraceRay( vec3 &start, vec3 &dir, vec3 power, int thisObjIndex, int thisObjPartIndex, Scene *scene, bool specularDone, int depth )

{
  vec3 intPoint, intNorm, intTexCoords;
  float t;
  int objIndex, objPartIndex;
  Material *mat;


  // YOUR CODE HERE
  //
  // 1. Find first object hit by photon.
  // 
  // 
  // 2. Store the photon if it has already has a specular reflection and if this is a diffuse surface.
  // 
  // 3. Stop if at max depth.
  // 
  // 
  // 4. Find the probability that the photon continues.
  // 
  // 5. Generate random number.  If that shows that the photon dies, return.
  // 
  // 6. Probabilistically determine the action (one of diffuse or
  //      specular reflection for all surfaces, plus refracted
  //      transmission for non-opaque surfaces).  Based on the action,
  //      compute the power loss (maybe!) and a direction to follow.
  // 
  // 7. Send the photon onward with recursive call to forwardTraceRay().
  
 // srand(time(NULL));

  // from raytrace()
  // Terminate the ray?

  depth++;

  // find first object hit
  bool hit = scene->findFirstObjectInt(start, dir, thisObjIndex, thisObjPartIndex, intPoint, intNorm, intTexCoords, t, objIndex, objPartIndex, mat, -1);

  if (!hit)
      return;  // No intersection: Return background colour

  Object& obj = *scene->objects[objIndex];

  float textureAlpha;
  vec3  textureColour = obj.textureColour(intPoint, objPartIndex, textureAlpha, intTexCoords); // (also sets 'textureAlpha')

  vec3  kd = vec3(textureColour.x * mat->kd.x, textureColour.y * mat->kd.y, textureColour.z * mat->kd.z);
  float alpha = textureAlpha * mat->alpha;

  bool isInsideObject = (dir * intNorm > 0);
  bool isDiffuse = false;

  vec3 ks = mat->ks;
  //vec3 kd = mat->kd; 
 
  // finding max of the rgb components
  float maxKs = max(max(ks.x, ks.y), ks.z);
  float maxKd = max(max(kd.x, kd.y), kd.z);

  float ps = mat->alpha * (maxKs / (maxKs + maxKd)); // probability of specular reflection
  float pd = mat->alpha * (maxKd / (maxKs + maxKd)); // probability of diffuse reflection in random direction
  float pt = (1 - mat->alpha);                       // probability of refraction (opacity)

  if (maxKd > 0) {
      isDiffuse = true;
  }

  // store photon
  if (specularDone && isDiffuse && !isInsideObject) {
      photons.add(new Photon(intPoint, dir, power));
  }

  // if at maxDepth, stop
  if (depth >= scene->maxDepth) {
      return; 
  }
  
  bool refractionOccurs = false;

  //vec3 V = (scene->eye->position - start);
  vec3 refractionDir; 
  vec3 reflectionDir = 2 * (intNorm * dir) * intNorm - dir;
  vec3 reflectedPower = power; 

  // Probabilistically determine action
  float randomNum = (float)rand() / RAND_MAX;
  if (ps > randomNum) {
      reflectedPower = vec3(power.x / ps , power.y / ps , power.z / ps ); // calculating specular reflection power
      forwardTraceRay(start, reflectionDir, reflectedPower, thisObjIndex, thisObjPartIndex, scene, true, depth);
  }
  else if (pd > randomNum) {
      // reflectedPower
      reflectedPower = vec3(power.x / ps, power.y / ps, power.z / ps); // calculating specular reflection power
      
      if (scene->findRefractionDirection(dir, intNorm, refractionDir)) { // if refraction occurs
          forwardTraceRay(start, reflectionDir, reflectedPower, thisObjIndex, thisObjPartIndex, scene, true, depth);
      }
  }
  else if (pt > randomNum) {
      refractionOccurs = scene->findRefractionDirection(dir, intNorm, refractionDir);
      forwardTraceRay(start, refractionDir, reflectedPower, thisObjIndex, thisObjPartIndex, scene, specularDone, depth);

  }

}



// ----------------------------------------------------------------
//
//  KD Tree
//
// ----------------------------------------------------------------



// Build the KD tree from a list of photons


void KDTree::buildFromPhotons( seq<Photon*> &photons, vec3 &min, vec3 &max )

{
  // Find the bounding box
  
  min = vec3(MAXFLOAT,MAXFLOAT,MAXFLOAT);
  max = vec3(-MAXFLOAT,-MAXFLOAT,-MAXFLOAT);

  for (int i=0; i<photons.size(); i++) {
    if (photons[i]->pos.x < min.x) min.x = photons[i]->pos.x;
    if (photons[i]->pos.y < min.y) min.y = photons[i]->pos.y;
    if (photons[i]->pos.z < min.z) min.z = photons[i]->pos.z;
    if (photons[i]->pos.x > max.x) max.x = photons[i]->pos.x;
    if (photons[i]->pos.y > max.y) max.y = photons[i]->pos.y;
    if (photons[i]->pos.z > max.z) max.z = photons[i]->pos.z;
  }

  // Build the tree
  
  root = root->buildSubtreeFromPhotons( &photons[0], photons.size(), min, max );
}



// Used below to sort photon on one of the three axes (specified by
// 'splitDir')


#ifdef MACOS
  int comparePhotonPs( int* splitDir, Photon** p1, Photon** p2)
#else
  #ifdef _WIN32
    int comparePhotonPs( int* splitDir, Photon **p1, Photon **p2 )
  #else // LINUX
    int comparePhotonPs( Photon** p1, Photon** p2, int* splitDir )
  #endif  
#endif

{
  int i = *splitDir;

  if ((*p1)->pos[i] < (*p2)->pos[i])
    return -1;
  else if ((*p1)->pos[i] > (*p2)->pos[i])
    return +1;
  else
    return 0;
}



// Given an array of n photons, and the min and max of the bounding
// box, return a pointer to a KD tree of the photons.


KDSubtree * KDSubtree::buildSubtreeFromPhotons( Photon **photons, int n, vec3 &min, vec3 &max )

{
  // Empty tree?
  
  if (n <= 0)
    return NULL;

  // Choose the greatest dimension along which to split

  int splitDir;		// x=0, y=1, z=2

  float xWidth = max.x - min.x;
  float yWidth = max.y - min.y;
  float zWidth = max.z - min.z;

  if (xWidth >= yWidth && xWidth >= zWidth)
    splitDir = 0;
  else if (yWidth >= xWidth && yWidth >= zWidth)
    splitDir = 1;
  else
    splitDir = 2;

  // Find median in the split direction
  //
  // We'll do this by sorting in O(n log n), but in production code
  // would really do O(n) median finding.

#ifdef MACOS
  qsort_r( photons, n, sizeof(Photon*), &splitDir, (int (*)(void*, const void *, const void *)) comparePhotonPs );
#else
  #ifdef _WIN32
    qsort_s(photons, n, sizeof(Photon*), (int (*) (void*, const void*, const void*)) comparePhotonPs, &splitDir);
  #else // LINUX
    qsort_r(photons, n, sizeof(Photon*), (int (*)(const void*, const void*, void*)) comparePhotonPs, &splitDir);
  #endif
#endif

  int medianIndex = n/2;
  Photon *medianPhoton = photons[medianIndex];

  // Find the bounding boxes of the two groups of photons, split at the medianPhoton
  
  vec3 minLeft = min; 
  vec3 maxLeft = max;
  maxLeft[splitDir] = medianPhoton->pos[splitDir];

  vec3 minRight = min; 
  vec3 maxRight = max;
  minRight[splitDir] = medianPhoton->pos[splitDir];

  // Construct the root and recursively attach the two subtrees

  return new KDSubtree( splitDir, 
			medianPhoton, 
			buildSubtreeFromPhotons( photons,                   medianIndex,       minLeft,  maxLeft ),
			buildSubtreeFromPhotons( photons + (medianIndex+1), n-(medianIndex+1), minRight, maxRight ) );
}



// Return a list of photons that are closest to 'pos'.  The list will
// contain the most distant photon first and the least distant photon
// last.  At most 'maxCount' photons are returned and all must be
// within 'maxSqDist' (max *squared* distance).
 

seq<Photon*> * KDTree::findNearest( vec3 &pos, float maxSqDist, int maxCount )

{
  // Use a priority queue (a heap) with the priority = the squared
  // distance from 'pos'.  The queue stores the max-priority element
  // at the top.

  priority_queue<Photon*> queue;

  // Find the closest photons
  //
  // Traverse the tree, going into those subtrees that are within
  // distance 'maxDist' of 'pos'

  if (root != NULL)
    root->findSubtreeNearest( pos, maxSqDist, maxCount, queue );

  // Package the result

  seq<Photon*> * photons = new seq<Photon*>( queue.n );

  while (!queue.empty())
    photons->add( queue.remove_max() );

  return photons;
}



// Within this subtree, collect the nearest photons


void KDSubtree::findSubtreeNearest( vec3 &pos, float maxSqDist, int maxCount, priority_queue<Photon*> &queue )

{
  // If the photon in this subtree's root is close enough, add it

  vec3 diff = pos - photon->pos;

  float sqdist = diff.squaredLength();

  if (sqdist < maxSqDist) {
    queue.add( photon, sqdist );
    if (queue.n > maxCount)
      queue.remove_max();
  }

  // Check for overlap with the children

  float distToSeparator = diff[splitDir]; // distance from pos to plane that separates the children
  
  if (left != NULL &&
      (distToSeparator <= 0 ||	// on left side
       diff[splitDir] * diff[splitDir] < maxSqDist)) // overlaps left side

    left->findSubtreeNearest( pos, maxSqDist, maxCount, queue );

  if (right != NULL &&
      (distToSeparator >= 0 ||	// on right side
       diff[splitDir] * diff[splitDir] < maxSqDist)) // overlaps right side

    right->findSubtreeNearest( pos, maxSqDist, maxCount, queue );
}




// ----------------------------------------------------------------
//
//   Drawing the photon map and KD tree
//
// ----------------------------------------------------------------



// Draw one subtree (as long as numLevels > 0)


void KDSubtree::draw( vec3 &min, vec3 &max, int numLevels, mat4 &WCS_to_VCS, mat4 &WCS_to_CCS, vec3 lightDir )

{
  // Draw the partition

  vec3 c00, c10, c11, c01;

  vec3 &pos = photon->pos;

  // Find the partition corners
  
  switch (splitDir) {
  case 0: // X
    c00 = vec3( pos.x, min.y, min.z );
    c10 = vec3( pos.x, max.y, min.z );
    c11 = vec3( pos.x, max.y, max.z );
    c01 = vec3( pos.x, min.y, max.z );
    break;
  case 1: // Y
    c00 = vec3( min.x, pos.y, min.z );
    c10 = vec3( max.x, pos.y, min.z );
    c11 = vec3( max.x, pos.y, max.z );
    c01 = vec3( min.x, pos.y, max.z );
    break;
  case 2: // Z
    c00 = vec3( min.x, min.y, pos.z );
    c10 = vec3( max.x, min.y, pos.z );
    c11 = vec3( max.x, max.y, pos.z );
    c01 = vec3( min.x, max.y, pos.z );
    break;
  }

  // Draw the rectangular partition

  vec3 pts[4] = { vec3( c00 ), vec3( c10 ), vec3( c11 ), vec3( c01 ) };

  scene->segs->drawSegs( GL_LINE_LOOP, &pts[0], GREY_COLOUR, 4, WCS_to_VCS, WCS_to_CCS, lightDir );

  // Find the bounding boxes of the two subtrees

  numLevels--;

  if (numLevels > 0) {

    vec3 leftMax = max;
    vec3 rightMin = min;

    leftMax[splitDir] = pos[splitDir];
    rightMin[splitDir] = pos[splitDir];

    // Recursively draw the two subtrees

    if (left != NULL)
      left->draw( min, leftMax, numLevels, WCS_to_VCS, WCS_to_CCS, lightDir );
    if (right != NULL)
      right->draw( rightMin, max, numLevels, WCS_to_VCS, WCS_to_CCS, lightDir );
  }
}



// Draw the bounding box, then draw the tree


void KDTree::draw( vec3 &min, vec3 &max, int treeDisplayDepth, mat4 &WCS_to_VCS, mat4 &WCS_to_CCS, vec3 lightDir )


{
  // Draw bounding box

  vec3 pts[24] = {
    vec3(min.x, min.y, min.z),
    vec3(min.x, min.y, max.z),
    vec3(min.x, max.y, min.z),
    vec3(min.x, max.y, max.z),
    vec3(max.x, min.y, min.z),
    vec3(max.x, min.y, max.z),
    vec3(max.x, max.y, min.z),
    vec3(max.x, max.y, max.z),
    vec3(min.x, min.y, min.z),
    vec3(max.x, min.y, min.z),
    vec3(min.x, min.y, max.z),
    vec3(max.x, min.y, max.z),
    vec3(min.x, max.y, min.z),
    vec3(max.x, max.y, min.z),
    vec3(min.x, max.y, max.z),
    vec3(max.x, max.y, max.z),
    vec3(min.x, min.y, min.z),
    vec3(min.x, max.y, min.z),
    vec3(min.x, min.y, max.z),
    vec3(min.x, max.y, max.z),
    vec3(max.x, min.y, min.z),
    vec3(max.x, max.y, min.z),
    vec3(max.x, min.y, max.z),
    vec3(max.x, max.y, max.z)
  };

  scene->segs->drawSegs( GL_LINES, pts, GREY_COLOUR, 24, WCS_to_VCS, WCS_to_CCS, lightDir );

  // Draw the tree partitions

  if (root != NULL && treeDisplayDepth > 0)
    root->draw( min, max, treeDisplayDepth, WCS_to_VCS, WCS_to_CCS, lightDir );
}



// Draw the photons and the KD tree


void PhotonMap::draw( seq<Photon*> &photonsToHighlight, mat4 &WCS_to_VCS, mat4 &WCS_to_CCS, vec3 lightDir )

{
  // Draw partitions

  if (tree != NULL)
    tree->draw( c000, c111, treeDisplayDepth, WCS_to_VCS, WCS_to_CCS, lightDir );

  // Draw photons with direction lines

  int nPhotons = photons.size();

  if (photons.size() > 0) {

    seq<vec3> lightPoints(nPhotons), darkPoints(nPhotons), lightLines(2*nPhotons), darkLines(2*nPhotons);

    vec3 lightOrange( 0.9, 0.7, 0.2 );
    vec3 darkOrange(  0.7, 0.3, 0.1 );
    
    // Photons

    for (int i=0; i<nPhotons; i++) {

      if (photonsToHighlight.exists( photons[i] )) {
	lightPoints.add( photons[i]->pos );
	vec3 head = photons[i]->pos + 0.03 * photons[i]->dir;
	lightLines.add( photons[i]->pos );
	lightLines.add( head );
      } else {
	darkPoints.add( photons[i]->pos );
	vec3 head = photons[i]->pos + 0.03 * photons[i]->dir;
	darkLines.add( photons[i]->pos );
	darkLines.add( head );
      }
    }

    glPointSize( 6.0 );
    scene->segs->drawSegs( GL_POINTS, lightPoints.array(), lightOrange, lightPoints.size(), WCS_to_VCS, WCS_to_CCS, lightDir );
			              
    glPointSize( 3.0 );	              
    scene->segs->drawSegs( GL_POINTS, darkPoints.array(),  darkOrange,  darkPoints.size(), WCS_to_VCS, WCS_to_CCS, lightDir );
			              
    scene->segs->drawSegs( GL_LINES,  lightLines.array(),  lightOrange, lightLines.size(), WCS_to_VCS, WCS_to_CCS, lightDir );
			              
    scene->segs->drawSegs( GL_LINES,  darkLines.array(),   darkOrange,  darkLines.size(), WCS_to_VCS, WCS_to_CCS, lightDir );
  }
}
