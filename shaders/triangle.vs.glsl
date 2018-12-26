#version 330

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexCoords;
layout(location = 2) in vec3 aVertexColor;


out vec2 vFragTexture;
out vec3 vFragColor;

void main() {

	vFragTexture = aVertexTexCoords;
	vFragColor = aVertexColor;
    gl_Position = vec4((vec3(aVertexPosition,1)).xy, 0, 1);
	
}
