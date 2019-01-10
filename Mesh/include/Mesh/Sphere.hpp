/**
* \file:  Sphere.hpp
* \brief Decalaration of the class "Sphere"
*/

#ifndef __SPHERE__HPP
#define __SPHERE__HPP

#include <iostream>
#include <Render/Texture.hpp>
#include <glimac/Shader.hpp>
#include "Mesh.hpp"
#include <vector>
#include <string>


class Sphere : public Mesh {
public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong) : Mesh(nullptr,nullptr) {
    	m_nbVertex = 0;
        build(radius, discLat, discLong); // Construction (voir le .cpp)
    }

    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

};

#endif
