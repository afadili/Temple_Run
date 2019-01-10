/**
 * \file ShaderManager.hpp
 * \brief description : Declaration of the class "ShaderManager"
 */

#ifndef __SHADERMANAGER__HPP
#define __SHADERMANAGER__HPP

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>

#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>

#include <Error/Error.hpp>

/**
 * \class ShaderManager
 * \brief manage the shaders program and their uniform variables 
 */
class ShaderManager {
private:
  glimac::Program m_program;
  glimac::FilePath m_vsPath;
  glimac::FilePath m_fsPath;
  std::map<std::string, GLint> m_uMap;

private:
  /**
   * \brief constructor of Shader
   */
  ShaderManager() = default;

public:
  /**
   * \brief constructor of Shader
   * \param vs : filepath of the vs file
   * \param fs : filepath of the fs file
   */
  ShaderManager(const glimac::FilePath &vs, const glimac::FilePath &fs);

  /**
   * \brief destructor of Shader
   */
  ~ShaderManager() = default;


  /**
   * \brief adding a uniform variable
   * \param name : the name of the uniform variable
   */
  void addUniform(const std::string &name);

  /**
   * \brief Sends a uniform variable of type Matrix4f
   * \param name : the name of the uniform variable
   * \param value : the value to send
   */
  void sendUniformMatrix4fv(std::string name, glm::mat4 value);

  /**
   * \brief Sends a uniform variable of type vec3f
   * \param name : the name of the uniform variable
   * \param value : the value to send
   */
  void sendUniform3f(std::string name, glm::vec3 value);

  /**
   * \brief Sends a uniform variable of type int
   * \param name : the name of the uniform variable
   * \param num : the value to send
   */
  void sendUniform1i(std::string name, int num);

  /**
   * \brief Sends a uniform variable of type float
   * \param name : the name of the uniform variable
   * \param num : the value to send
   */
  void sendUniform1f(std::string name, float num);

  /**
   * \brief use this shader
   */
  void use();

  /**
   * \brief getter of the id
   * \return the id of the program
   */
  inline
  GLuint id() const {
    return m_program.getGLId();
  }

  /**
   * \brief Opérateur << for print shader data
   */
  friend std::ostream &operator<<(std::ostream &os, const ShaderManager &shader) {
    // Print vs and fs path
    os << "  -- VS path = \"" << shader.m_vsPath << "\"\n";
    os << "  -- FS path = \"" << shader.m_fsPath << "\"\n";
    // Print position
    os << "  -- Uniform Matrix = {\n";
    for (std::pair<std::string, GLuint> map : shader.m_uMap)
      os << "      " << map.first << " = " << map.second << std::endl;
    os << "  }\n";
    return os;
  }

};


#endif
