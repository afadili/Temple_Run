#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet


out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
  //fFragColor.rgb = vec3(1,0,0);
  fFragColor.rgb = texture(uTexture, vTexCoords).rgb;
};