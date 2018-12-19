#include <Render/IBO.hpp>

IBO::IBO() : Render() {
    glGenBuffers(1, &m_ID);
}

IBO::~IBO(){}

void IBO::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IBO::debind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}