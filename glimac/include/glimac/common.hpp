#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
	ShapeVertex();
	ShapeVertex(const glm::vec3 &vecPos, const glm::vec3 &vecNormal, const glm::vec2 &vecTex) : position(vecPos), normal(vecNormal), texCoords(vecTex) {}

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

}
