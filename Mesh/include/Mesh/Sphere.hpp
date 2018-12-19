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


// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)

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
