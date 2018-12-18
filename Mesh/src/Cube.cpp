#include <GL/glew.h>
#include <glimac/common.hpp>
#include <Mesh/Cube.hpp>

Cube::Cube() : Mesh() {
	generateVertices(glm::vec3(1.,1.,1.));
	generateIndexs();
}

Cube::Cube(const glm::vec3 &width) : Mesh() {
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
	// Center the mesh 
	glm::vec3 upper = glm::vec3(width.x/2., width.y/2., width.z/2.);
	glm::vec3 lower = glm::vec3(-width.x/2., -width.y/2., -width.z/2.);

	// FRONT FACE
    m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, upper.z), glm::vec3(upper.x, upper.y, upper.z), glm::vec2(1,1))); // TOP RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, upper.z), glm::vec3(upper.x, lower.y, upper.z), glm::vec2(1,0))); // BOTTOM RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, upper.z), glm::vec3(lower.x, lower.y, upper.z), glm::vec2(0,0))); // BOTTOM LEFT
    m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, upper.z), glm::vec3(lower.x, upper.y, upper.z), glm::vec2(0,1))); // TOP LEFT

    // BACK FACE
    m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, lower.z), glm::vec3(upper.x, upper.y, lower.z), glm::vec2(1,1))); // TOP RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, lower.z), glm::vec3(upper.x, lower.y, lower.z), glm::vec2(1,0))); // BOTTOM RIGHT
    m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, lower.z), glm::vec3(lower.x, lower.y, lower.z), glm::vec2(0,0))); // BOTTOM LEFT
    m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, lower.z), glm::vec3(lower.x, upper.y, lower.z), glm::vec2(0,1))); // TOP LEFT
}

void Cube::generateIndexs(){
	m_indexVer.insert(m_indexVer.end(), { 0, 1, 2, 0, 2, 3 }); // FRONT FACE
	m_indexVer.insert(m_indexVer.end(), { 4, 5, 6, 4, 6, 7 }); // BACK FACE
	m_indexVer.insert(m_indexVer.end(), { 0, 1, 4, 1, 4, 5 }); // RIGHT FACE
	m_indexVer.insert(m_indexVer.end(), { 2, 3, 7, 2, 6, 7 }); // LEFT FACE
	m_indexVer.insert(m_indexVer.end(), { 0, 3, 4, 3, 4, 7 }); // TOP FACE
	m_indexVer.insert(m_indexVer.end(), { 1, 2, 5, 2, 5, 6 }); // BTTOM FACE
}