#version 330

in vec3 vPosition_vs; // Position of the transformed vertex in the View space
in vec3 vNormal_vs; // Normal of the transformed summit in the View space

out vec3 fFragColor; // Output color

void main() {
  fFragColor.rgb = vec3(1,0,1);
}
