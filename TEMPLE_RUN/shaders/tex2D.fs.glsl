#version 330

in vec2 vFragTexture;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
    fFragColor = vec3(1,0,0);
    fFragColor.rgb = texture(uTexture, vFragTexture).rgb;
}
