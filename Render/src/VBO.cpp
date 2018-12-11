#include "Buffer.hpp"
#include "VBO.hpp"

VBO::VBO(){
	glGenBuffers(1, &m_ID);
}

VBO::~VBO(){
	glDeleteBuffers(1, &m_ID);
}

void VBO::bind(){
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::debind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}