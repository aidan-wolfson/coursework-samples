// Pass 2 vertex shader
//
// Output vertex colour, WCS normal, WCS postion, texture coordinates

#version 300 es
precision mediump float;

uniform mat4 OCS_to_WCS;	// vertex OCS to WCS
uniform mat4 OCS_to_CCS;	// vertex OCS to eye CCS
uniform bool texturing;		// =1 if texturing is turned on

layout (location=0) in vec3 vertPosition;  // vertex position in OCS
layout (location=1) in vec3 vertNormal;    // vertex normal in OCS
layout (location=2) in vec2 vertTexCoords; // vertex texture coordinates

out vec3 colour;		// vertex colour
out vec3 normal;		// vertex normal in WCS (for light fixed in WCS)
out vec3 wcsPosition;		// vertex position in WCS
out vec2 texCoords;		// vertex texture coords (copied)
// phong parameters
out vec3 diffuseCoeff;
out vec3 specularCoeff;
out vec3 lightAmbient;
out vec3 lightEmissive;
out float n;

uniform vec3 kd;
uniform vec3 ks;
uniform vec3 Ia;
uniform vec3 Ie;
uniform float shininess; 


void main()

{
  // calculate vertex position in eye's CCS.  Store this in gl_Position.

  //gl_Position = vec4(0,0,0,1);   // CHANGE THIS
  gl_Position = OCS_to_CCS*vec4(vertPosition,1);

  // Provide a colour from the wavefront model (see 'setMaterial' in
  // wavefront.cpp).  If doing Phong, also output other Phong
  // parameters from the wavefront model, to be used as input to
  // pass2.frag.

  colour = kd;		// CHANGE THIS
  specularCoeff = ks;
  lightAmbient = Ia;
  lightEmissive = Ie;
  n = shininess;

  // calculate normal in WCS.  (Do not divide by w since this is a direction and w = 0.)

  normal = vec3(OCS_to_WCS*vec4(vertNormal,0));

  // Calculate position in WCS

  wcsPosition = vec3(OCS_to_WCS*vec4(vertPosition,1)/OCS_to_WCS[3][3]);	// CHANGE THIS

  // Copy texture coords to frag shader

  if (texturing)
    texCoords = vertTexCoords;
  }
