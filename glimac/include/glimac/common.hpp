#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

  struct ShapeVertex {
    ShapeVertex();

    ShapeVertex(const glm::vec3 &vecPos, const glm::vec3 &vecNormal, const glm::vec2 &vecTex) : position(vecPos), normal(vecNormal), texCoords(vecTex) {
    }

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
  };

  static inline bool isSpace(const char c) {
    return (c == ' ') || (c == '\t');
  }

  static inline bool isNewLine(const char c) {
    return (c == '\r') || (c == '\n') || (c == '\0');
  }

  static inline std::string parseString(const char*& token) {
    std::string s;
    int b = strspn(token, " \t");
    int e = strcspn(token, " \t\r");
    s = std::string(&token[b], &token[e]);

    token += (e - b);
    return s;
  }

  static inline int parseInt(const char*& token) {
    token += strspn(token, " \t");
    int i = atoi(token);
    token += strcspn(token, " \t\r");
    return i;
  }

  static inline float parseFloat(const char*& token) {
    token += strspn(token, " \t");
    float f = (float) atof(token);
    token += strcspn(token, " \t\r");
    return f;
  }

  static inline void parseFloat2(float& x, float& y, const char*& token) {
    x = parseFloat(token);
    y = parseFloat(token);
  }

  static inline void parseFloat3(float& x, float& y, float& z, const char*& token) {
    x = parseFloat(token);
    y = parseFloat(token);
    z = parseFloat(token);
  }


}
