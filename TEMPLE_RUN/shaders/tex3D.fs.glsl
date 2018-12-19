#version 330 core

in vec3 vPosition_vs; // Position of the transformed vertex in the View space
in vec3 vNormal_vs; // Normal of the transformed summit in the View space
in vec2 vTexCoords; // Texture coordinates

out vec3 fFragColor; // Output color

uniform sampler2D uTexture;

void main() {
  fFragColor.rgb = texture(uTexture, vTexCoords).rgb;
};