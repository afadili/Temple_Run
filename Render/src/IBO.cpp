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

template <typename type>
void IBO::fillBuffer(std::vector<type> &vect){
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vect.size() * sizeof(type), vect.data(), GL_STATIC_DRAW);
    debind();
};