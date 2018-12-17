#include <Render/VAO.hpp>

VAO::VAO() : Render() {
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

template <typename type>
void VAO::fillBuffer(std::vector<type> &vect, VBO *vbo){
	bind();
        
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    vbo->bind();
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*) offsetof(type, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*) offsetof(type, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*) offsetof(type, texCoords));
    vbo->debind();
    debind();
}