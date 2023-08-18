// front.frag

#version 300 es

#define SURFACE 0		// renderType
#define DRR     1
#define MIP     2

precision highp float;

uniform sampler2D texture_fbo;
uniform mediump sampler3D texture_volume;
uniform mediump sampler3D texture_gradient; // normals in OCS

uniform float fbWidth;
uniform float fbHeight;
uniform float slice_spacing;
uniform float densityFactor;
uniform float shininess;

uniform int   renderType;
uniform int   invert;
uniform int   useSpecular;

uniform vec3 light_direction;
uniform vec3 lightColour;
uniform vec3 volumeScale;

uniform mat4 MVinverse;

in vec3 texCoords;		// texCoords on front face of volume
in vec3 fragPosition;		// fragment position in VCS

out vec4 fragColour;



void main()

{
  // Get cube's front texCoords 

  vec3 frontCoords = texCoords;  // [YOUR CODE HERE]

#if 0 // testing
  fragColour = vec4( frontCoords, 1 );
  return;
#endif

  // Compute texture coordinate of this fragment in the 2D FBO.  These
  // texture coordinates are in [0,1]x[0,1].
  //
  // Use the implicitly-defined 'gl_FragCoord', which is the PIXEL
  // POSITION of the fragment in the framebuffer in the range
  //
  //    [0,width-1] x [0,height-1]
  //
  // where 'width' and 'height' are the dimensions of the framebuffer.

  vec2 fboCoords = vec2(gl_FragCoord.x / fbWidth, gl_FragCoord.y / fbHeight); // [YOUR CODE HERE]

#if 0 // testing.  zoom in to make the bounding volume fill the whole screen.
  fragColour  = vec4( fboCoords.x, fboCoords.y, 0, 1 );
  return;
#endif

  // Get cube's back texCoords
  //
  // These are stored in the FBO texture.

  //vec3 backCoords = vec3(0,0,1); // [YOUR CODE HERE]
  vec3 backCoords = texture(texture_fbo, fboCoords).xyz;

#if 0 // testing
  fragColour = vec4( backCoords, 1 );
  return;
#endif

  // determine front-to-back distance in WORLD COORDINATES.  You'll
  // have to scale the [0,1]x[0,1]x[0,1] texture coordinates by
  // 'volumeScale' to get the world coordinates, and then compute the
  // distance.

  //float dist = 0.5;  // [YOUR CODE HERE]
  float dist = length(((texCoords - backCoords) * volumeScale)); 

#if 0 // testing.  You should see different distances in the bounding volume.
  fragColour = vec4( dist, dist, dist, 1 );
  return;
#endif

  // Determine the NORMALIZED viewing direction along this ray back
  // toward the eye.  Then move this into the OCS, since the gradients
  // (i.e. surface normals) are in the OCS and all lighting
  // calculations should take place in the OCS.

  //vec3 viewDir = vec3(1,0,0);

  vec3 viewDir = normalize(MVinverse*vec4(vec3(0,0,1) - fragPosition,0)).xyz;

#if 0 // testing
  fragColour = vec4( 0.5 * (viewDir + vec3(1,1,1)), 1 );
  return;
#endif

  // Step front-to-back, accumulating colour
  //
  // Use the correct spacing in texture coordinates.
  //
  // See the lecture notes for details here.
  //
  // When computing alpha at a position inside the volume, MULTIPLY IT
  // BY THE UNIFORM 'densityFactor', which the user controls by
  // pressing '+' or '-' to make things appear more or less dense.

  //vec3 Iout = vec3( 0.7, 0.3, 0.4 );
  vec3 Iout = vec3( 0, 0, 0 );
  vec3 Ibacklight = vec3(1,1,1);
  float trans = 1.0; // update this as we go. t(0) = 1
  vec3 ks = vec3(1,1,1);
  vec3 kd = lightColour;

#if 1
  // loop from i=0 to i=n (where n = dist)
  for (float s = 0.0; s < dist; s = s + dist/slice_spacing) {
    // Gather tau, alpha, and the gradient

    // [YOUR CODE HERE]
    //float tau = texture(texture_volume, backCoords + s * viewDir).x;
    float tau = texture(texture_volume, frontCoords - s * viewDir).x;
    float alpha = tau*slice_spacing*densityFactor; // delta s * tau

    // gradient
    vec3 lt = frontCoords + s*slice_spacing * normalize(backCoords - frontCoords);
    vec3 gradient = normalize(texture(texture_gradient, lt).xyz); // normalized gradient


    // Compute C based on the current 'renderType', which is one of
    // MIP, DRR, or SURFACE.
    //
    // Initially, do this only for the DRR, which is the simplest
    // computation.  (See the lecture notes on this.)

    vec3 C;

    // [YOUR CODE HERE]
    

    // Add this position's C to the accumulated colour, including the
    // appropriate alpha.
    //
    // How you do this will depend on the 'renderType'.
    if(renderType == SURFACE) 
    {
    // C = phong lighting
    C = kd * dot(gradient, light_direction) + ks*pow(dot(reflect(-light_direction,gradient),viewDir), shininess);
    //Iout = Iout + trans*C*alpha;
    trans = trans*(1.0 - alpha); // accumulated transparency
    Iout = Iout + trans*Ibacklight; 

    } else if (renderType == DRR) {
    // DO THiS FIRST
    // C(s) = (0,0,0) and only the backlight is attenuated by the accumulated t
    C = vec3(0,0,0);
    Iout = Iout + trans*C*alpha;
    trans = trans*(1.0 - alpha); // accumulated transparency
    Iout = Iout + trans*Ibacklight; 

    } else if (renderType == MIP) {

    }
    //break;
  }
#endif

  // Output

  if (invert == 1)
     Iout = vec3(1,1,1) - Iout;

  fragColour = vec4( Iout, 1 );
}
