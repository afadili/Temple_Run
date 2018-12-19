#include <GL/glew.h>
#include <glimac/common.hpp>
#include <Mesh/Cube.hpp>

Cube::Cube() : Mesh(nullptr, nullptr){
	generateVertices(glm::vec3(1.,1.,1.));
	generateIndexs();
}

Cube::Cube(const glm::vec3 &width) : Mesh(nullptr, nullptr) {
	generateVertices(width);
	generateIndexs();
}

Cube::Cube(ShaderManager *shader, Texture *texture) : Mesh(shader, texture) {
	generateVertices(glm::vec3(1.,1.,1.));
	generateIndexs();
}

Cube::Cube(const glm::vec3 &width, ShaderManager *shader, Texture *texture) : Mesh(shader, texture) {
	generateVertices(width);
	generateIndexs();
}


void Cube::generateVertices(const glm::vec3 &width){
    float w,h,t;
    w = width.x/2;        
    h = width.y/2;   
	t = width.z/2; 

	// FRONT FACE
	//										POSITION			NORMAL				TEXTURE
    m_vertices.push_back(ShapeVertex(glm::vec3(-w, -h, t), glm::vec3(0, 0, 1), glm::vec2(1,1))); // BOTTOM LEFT
    m_vertices.push_back(ShapeVertex(glm::vec3(w, -h, t), glm::vec3(0, 0, 1), glm::vec2(1,0))); // BOTTOM RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(w, h, t), glm::vec3(0, 0, 1), glm::vec2(0,0))); // TOP RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(-w, h, t), glm::vec3(0, 0, 1), glm::vec2(0,1))); // TOP LEFT

    // BACK FACE
	//										POSITION			NORMAL				TEXTURE
    m_vertices.push_back(ShapeVertex(glm::vec3(-w, -h, -t), glm::vec3(0, 0, -1), glm::vec2(1,1))); // TOP RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(w, -h, -t), glm::vec3(0, 0, -1), glm::vec2(1,0))); // BOTTOM RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(w, h, -t), glm::vec3(0, 0, -1), glm::vec2(0,0))); // BOTTOM LEFT
    m_vertices.push_back(ShapeVertex(glm::vec3(-w, h, -t), glm::vec3(0, 0, -1), glm::vec2(0,1))); // TOP LEFT
}

void Cube::generateIndexs(){
	m_indexVer.insert(m_indexVer.end(), { 0, 1, 2, 2, 3, 0 }); // FRONT FACE
	m_indexVer.insert(m_indexVer.end(), { 1, 5, 6, 6, 2, 1 }); // RIGHT FACE
	m_indexVer.insert(m_indexVer.end(), { 7, 6, 5, 5, 4, 7 }); // BACK FACE
	m_indexVer.insert(m_indexVer.end(), { 4, 0, 3, 3, 7, 4 }); // LEFT FACE
	m_indexVer.insert(m_indexVer.end(), { 4, 5, 1, 1, 0, 4 }); // BOTTOM FACE
	m_indexVer.insert(m_indexVer.end(), { 3, 2, 6, 6, 7, 3 }); // TOP FACE
}