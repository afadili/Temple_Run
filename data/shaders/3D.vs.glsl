#version 330

layout(location = 0) in vec3 aVertexPosition; // Vertex position
layout(location = 1) in vec3 aVertexNormal; // Normal vertex
layout(location = 2) in vec2 aVertexTexCoords; // Texture coordinates

// Transformation matrices received in uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Shader output
out vec3 vPosition_vs; // Position of the transformed vertex in the View space
out vec3 vNormal_vs; // Normal of the transformed summit in the View space
out vec2 vTexCoords; // Texture coordinates

void main() {
  // Passage in homogeneous coordinates
  vec4 vertexPosition = vec4(aVertexPosition, 1);
  vec4 vertexNormal = vec4(aVertexNormal, 0);

  // Calculation of output values
  vPosition_vs = vec3(uMVMatrix * vertexPosition);
  vNormal_vs = vec3(uNormalMatrix * vertexNormal);
  vTexCoords = aVertexTexCoords;

  // Calculation of the projected position
  gl_Position = uMVPMatrix * vertexPosition;
}