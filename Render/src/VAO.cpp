#include "Buffer.hpp"
#include "VAO.hpp"

VAO::VAO(){
	glGenVertexArrays(1, &m_ID);
}

VAO::~VAO(){
	glDeleteVertexArrays(1, &m_ID);
}

void VAO::bind(){
	glBindVertexArray(m_ID);
}

void VAO::debind(){
	glBindVertexArray(0);
}