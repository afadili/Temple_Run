#version 330

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexCoords;


uniform float uTime;

out vec2 vFragTexture;

mat3 rotate(float alpha)
{
	return mat3(vec3(cos(radians(alpha)),sin(radians(alpha)),0),vec3(-sin(radians(alpha)),cos(radians(alpha)),0),vec3(0,0,1));
}


void main() {

    gl_Position = vec4((rotate(uTime) * vec3(aVertexPosition,1)).xy, 0, 1);
	vFragTexture = aVertexTexCoords;
}
