// mushroom.cpp


#include "mushroom.h"
#include "main.h"
#include "worldDefs.h"


extern GLFWwindow* window;
#define LINE_HALFWIDTH_IN_PIXELS    2.0
#define MUSH_GEOM_SCALE             (0.27 * ROW_SPACING)
#define MUSH_GEOM_CENTRE            vec2(3.5,3.5)

GLuint Mushroom::VAO = 0;


void Mushroom::generateVAOs()

{
      // [YOUR CODE HERE]
      //
      // REPLACE THE CODE in this function to generate VAOs that store
      // mushroom geometry.  You will need MULTIPLE VAOs.  You should look
      // at the Player and the Centipede to see how those multiple VAOs
      // are set up.  You can do something similar here, or take your own
      // approach.
      //
      // For full marks, you should use the parameters in worldDefs.h to
      // determine the SIZE of your geometry.
      //
      // Your geometry should be centred at (0,0) so that you can later
      // translate it to its correct position
      //
      // In Step 5 (after you get the mushroom rendered correctly), also
      // take into account the mushroom's 'damage' to draw a mushroom with
      // the appropriate amount of damage.

      // Start setting up a VAO
  
      // find line width is world coordinate system

      int width, height;
      glfwGetFramebufferSize( window, &width, &height );
      // dividing lw by scaling factor to keep lines thick
      float lw = (LINE_HALFWIDTH_IN_PIXELS / (float) height * 2)/MUSH_GEOM_SCALE; // relies on top-bottom = 2 in WCS

      // STORING GEOMETRY SEQUENCES
      vec2 bodyGeometry[MUSH_BODY_GEOM_COUNT] = {

        // Stem vertices
        vec2(+0.40 - lw, 0 - lw),
        vec2(+0.40 + lw, 0 + lw),
        vec2(-0.40 + lw, 0 - lw),
        vec2(-0.40 - lw, 0 + lw),
        vec2(-0.40 + lw, -1 + lw), // 1
        vec2(-0.40 - lw, -1 - lw), // 2
        vec2(+0.40 - lw, -1 + lw), // 3...
        vec2(+0.40 + lw, -1 - lw),
        vec2(+0.40 - lw, 0 - lw),
        vec2(+0.40 + lw, 0 + lw),
        // Head vertices
        vec2(+1-lw, 0.1-lw),
        vec2(+1+lw, 0.1+lw),
        vec2(1-lw, 0.70-lw),
        vec2(1+lw, 0.70+lw),
        vec2(0.2-lw, 1.4-lw),
        vec2(0.2+lw, 1.4+lw),
        vec2(-0.2+lw, 1.4-lw),
        vec2(-0.2-lw, 1.4+lw),
        vec2(-1 + lw, 0.70 - lw),
        vec2(-1 - lw, 0.70 + lw),
        vec2(-1 + lw, 0.1 - lw),
        vec2(-1 - lw, 0.1 + lw),
        vec2(+0.40 - lw, 0 - lw),
        vec2(+0.40 + lw, 0 + lw)

      }; // vector array of body vertices

      vec2 bodyFillGeometry[MUSH_BODY_FILL_GEOM] = {
          // vertices to be used as a fill
          //vec2(-0.40 + lw, -1 + lw),
          //vec2(+0.40 - lw, -1 + lw),
          //vec2(+0.40 - lw, 0 - lw),
          //vec2(-0.40 + lw, 0 - lw),
          //vec2(-0.40 + lw, -1 + lw)
          
          // STEM
          vec2(0,-0.5), // vec 0 (center for fan)
          vec2(-0.40 + lw, -1 + lw),
          vec2(+0.40 - lw, -1 + lw),
          vec2(+0.40 - lw, 0 - lw),
          vec2(-0.40 + lw, 0 - lw),
          vec2(-0.40 + lw, -1 + lw)
      };

      vec2 headFillGeometry[MUSH_HEAD_FILL_GEOM] = {
          // HEAD
          vec2(0,0.7), // vec 0 (center for fan)
          vec2(0 + lw, 0 + lw),
          vec2(+1 - lw, 0.1 + lw),
          vec2(+1 - lw, 0.70 - lw),
          vec2(0.2 - lw, 1.4 - lw),
          vec2(-0.2 + lw, 1.4 - lw),
          vec2(-1 + lw, 0.70 - lw),
          vec2(-1 + lw, 0.1 + lw),
          vec2(0 + lw, 0 + lw)
      };

      vec2 damageGeometry[MUSH_DAMAGE_GEOM_COUNT] = {
          vec2(-1.05,-1.05),    // 1
          vec2(1.05,-1.05),     // 2 
          vec2(-1.05,1.45),     // 3

          vec2(1.05,-1.05),     // 2
          vec2(-1.05,1.45),     // 3
          vec2(1.05,1.45),      // 4

          vec2(1.05,1.45),      // 4 
          vec2(1.05,1.60),      // 5
          vec2(0.5,1.45),       // 6

          vec2(0.5,1.45),       // 6
          vec2(0,1.60),         // 7
          vec2(0,1.45),         // 8

          vec2(0,1.60),         // 7
          vec2(0,1.45),         // 8
          vec2(-0.5,1.45),      // 9

          vec2(-0.5,1.45),      // 9
          vec2(-1.05,1.60),     // 10
          vec2(-1.05,1.45)      // 3
      };


      // build the segments 
      // ------ SETTING UP BODY VAO ------
  
      glGenVertexArrays( 1, &VAO );
      glBindVertexArray( VAO );

      // Define the VBO
    
      GLuint VBO;
      glGenBuffers( 1, &VBO );
      glBindBuffer( GL_ARRAY_BUFFER, VBO );

      // Define the attributes

      glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0 ); // two floats for a position
      glEnableVertexAttribArray( 0 );

      glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (2*sizeof(float)) ); // three floats for a colour
      glEnableVertexAttribArray( 1 );

      // Define second (damage) VAO
      //GLuint damageVAO;

      glGenVertexArrays(1, &damageVAO);
      glBindVertexArray(damageVAO);

      // Define second (damage) VBO
      GLuint damageVBO;
      glGenBuffers(1, &damageVBO);
      glBindBuffer(GL_ARRAY_BUFFER, damageVBO);

      // Define the attributes

      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0); // two floats for a position
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))); // three floats for a colour
      glEnableVertexAttribArray(1);

      // Stop setting up this VAO.

      // set the VAO and VBO we're working on for the body
      glBindVertexArray( 0 );
      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      // ---------------- Set up the mushroom geometry ----------------
      //
 
      db = new DrawBuffers( VAO ); // DrawBuffers structure

      seq<vec2> positions; // vertex stream. will need to copy these to the VBO later
      seq<vec3> colours;

      GLuint offset; // offset to first vertex of the current piece of geometry

      // BUILDING THE OUTLINE OF THE MUSHROOM 
  
      offset = positions.size();
        
      // adding the positions 
      
      for (int i = 0; i < MUSH_BODY_GEOM_COUNT; i++) {
          // add vertices for triangle strip
          positions.add(MUSH_GEOM_SCALE * (bodyGeometry[i]));
          //positions.add(MUSH_GEOM_SCALE * (bodyGeometry[i + 1]));
          //positions.add(MUSH_GEOM_SCALE * (bodyGeometry[i + 2]));
      }
    
      // setting same colour for each vertex
      for (int i = offset; i < positions.size(); i++) {
        colours.add(MUSH_OUTLINE_COLOUR);
      }      

      // add geometry to DrawBuffers structure
      db->mode.add(GL_TRIANGLE_STRIP);
      db->first.add(0);
      db->count.add(positions.size() - offset);

      // CREATING THE STEM FILL
      offset = positions.size();

      for (int i = 0; i < MUSH_BODY_FILL_GEOM; i++) {
          positions.add(MUSH_GEOM_SCALE * bodyFillGeometry[i]);
      }
      
      for (int i = offset; i < positions.size(); i++) {
          colours.add(MUSH_BODY_COLOUR);
      }

      db->mode.add(GL_TRIANGLE_FAN);
      db->first.add(offset);
      db->count.add(positions.size() - offset);

      // CREATING THE HEAD FILL
      offset = positions.size();

      for (int i = 0; i < MUSH_HEAD_FILL_GEOM; i++) {
          positions.add(MUSH_GEOM_SCALE * headFillGeometry[i]);
      }

      for (int i = offset; i < positions.size(); i++) {
          colours.add(MUSH_BODY_COLOUR);
      }

      db->mode.add(GL_TRIANGLE_FAN);
      db->first.add(offset);
      db->count.add(positions.size() - offset);


      // ---------------- copy positions and colours to the VBO ----------------
      int numFloats = positions.size() * (2 + 3);
      float* buffer = new float[numFloats];
      float* p = buffer;

      for (int i = 0; i<positions.size(); i++) {
          *p++ = positions[i].x;
          *p++ = positions[i].y;
          *p++ = colours[i].x;
          *p++ = colours[i].y;
          *p++ = colours[i].z;
      }

      glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), buffer, GL_STATIC_DRAW);

      

      // Begin work on the damageVAO
      
      glBindVertexArray(damageVAO);
      glBindBuffer(GL_ARRAY_BUFFER, damageVBO);

      dbDamage = new DrawBuffers(damageVAO);

      seq<vec2> damagePositions; // vertex stream. will need to copy these to the VBO later
      seq<vec3> damageColours;

      offset = damagePositions.size();

      // add positions

      for (int i = 0; i < MUSH_DAMAGE_GEOM_COUNT; i++) {
          damagePositions.add(MUSH_GEOM_SCALE * damageGeometry[i]);
      }

      // add colours

      for (int i = offset; i < damagePositions.size(); i++) {
          damageColours.add(MUSH_DAMAGE_COLOUR);
      }
      
      dbDamage->mode.add(GL_TRIANGLES);
      dbDamage->first.add(offset);
      dbDamage->count.add(damagePositions.size() - offset);


      // ---------------- copy positions and colours to the VBO ----------------
      int numFloatsDamage = damagePositions.size() * (2 + 3);
      float* bufferDamage = new float[numFloatsDamage];
      float* pDamage = bufferDamage;

      for (int i = 0; i < damagePositions.size(); i++) {
          *pDamage++ = damagePositions[i].x;
          *pDamage++ = damagePositions[i].y;
          *pDamage++ = damageColours[i].x;
          *pDamage++ = damageColours[i].y;
          *pDamage++ = damageColours[i].z;
      }

      glBufferData(GL_ARRAY_BUFFER, numFloatsDamage * sizeof(float), bufferDamage, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      /*
      // This dummy code just builds a small square centred at (0,0).
      int numVerts  = 10;
      int numFloats = 5 * numVerts;  // five attributes for each vertex
  
      float *buffer = new float[ numFloats ];

      int i = 0;
  
      // Vertex 1
  
      buffer[i++] = -0.015 + lw;
      buffer[i++] = -0.015 + lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      buffer[i++] = -0.015 - lw;
      buffer[i++] = -0.015 - lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      // Vertex 2
  
      buffer[i++] = +0.015 - lw;
      buffer[i++] = -0.015 + lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      buffer[i++] = +0.015 + lw;
      buffer[i++] = -0.015 - lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      // Vertex 3
  
      buffer[i++] = +0.015 - lw;
      buffer[i++] = +0.015 - lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      buffer[i++] = +0.015 + lw;
      buffer[i++] = +0.015 + lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      // Vertex 4
  
      buffer[i++] = -0.015 + lw;
      buffer[i++] = +0.015 - lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      buffer[i++] = -0.015 - lw;
      buffer[i++] = +0.015 + lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      // and back to Vertex 1
  
      buffer[i++] = -0.015 + lw;
      buffer[i++] = -0.015 + lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      buffer[i++] = -0.015 - lw;
      buffer[i++] = -0.015 - lw;

      buffer[i++] = MUSH_OUTLINE_COLOUR.x;
      buffer[i++] = MUSH_OUTLINE_COLOUR.y;
      buffer[i++] = MUSH_OUTLINE_COLOUR.z;

      */

    }



    void Mushroom::draw( mat4 &worldToViewTransform )

    {
      // [YOUR CODE HERE]
      //
      // REPLACE THE CODE in this function so that your mushroom is drawn
      // centred at its 'pos'.
      //
      // Later, in Step 5, also take into account the mushroom's 'damage'
      // to draw a mushroom with the appropriate amount of damage.
  
      // Provide MVP to GPU program

      mat4 T = translate(pos.x, pos.y, 0);
      mat4 MVP = worldToViewTransform * T;

      gpuProg->setMat4( "MVP", MVP );

      db->draw();

      if (damage == 1) {
          mat4 T = translate(pos.x, pos.y - (2.4*MUSH_GEOM_SCALE), 0);
          mat4 MVP = worldToViewTransform * T;
          gpuProg->setMat4("MVP", MVP);
          dbDamage->draw();
      }
      else if (damage == 2) {
          mat4 T = translate(pos.x, pos.y - (2 * MUSH_GEOM_SCALE), 0);
          mat4 MVP = worldToViewTransform * T;
          gpuProg->setMat4("MVP", MVP);
          dbDamage->draw();
      }
      else if (damage == 3) {
          mat4 T = translate(pos.x, pos.y - (1 * MUSH_GEOM_SCALE), 0);
          mat4 MVP = worldToViewTransform * T;
          gpuProg->setMat4("MVP", MVP);
          dbDamage->draw();
      }

          //glBindVertexArray(0);
      //glBindVertexArray( VAO );


      //glDrawArrays( GL_TRIANGLE_STRIP, 0, 24 );
      //glDrawArrays(GL_TRIANGLES, 25, 6);

      //glBindVertexArray( 0 );
}

    DrawBuffers *Mushroom::db = NULL;
    DrawBuffers *Mushroom::dbDamage = NULL;


