#include <Render/IBO.hpp>

IBO::IBO(){
    glGenBuffers(1, &m_ID);
}

IBO::~IBO(){}

void IBO::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IBO::debind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}