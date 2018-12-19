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

class ShaderManager {
private:
  glimac::Program m_program;
  glimac::FilePath m_vsPath;
  glimac::FilePath m_fsPath;
  std::map<std::string, GLint> m_uMap;

public:
  //GLuint m_nGLId;

  /**
   * \brief constructor of Shader
   */
  ShaderManager() = default;

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
   * \brief 
   * \param name :
   */
  void addUniform(const std::string &name);

  /**
   * \brief 
   * \param name :
   * \param value :
   */
  void sendUniformMatrix4fv(std::string name, glm::mat4 value);

  /**
   * \brief 
   * \param name :
   * \param value :
   */
  void sendUniform3f(std::string name, glm::vec3 value);

  /**
   * \brief 
   * \param value :
   * \param num :
   */
  void sendUniform1i(std::string name, int num);

  /**
   * \brief 
   * \param name :
   * \param num :
   */
  void sendUniform1f(std::string name, float num);

  /**
   * \brief 
   */
  void use();

  //GLuint getGLId() const;
  inline
  GLuint id() const {
    return m_program.getGLId();
  }

  /**
   * \brief Opérateur << for print a mesh data
   */
  friend std::ostream &operator<<(std::ostream &os, const ShaderManager &shader) {
    // Print position
    os << "-- Uniform Matrix = {\n";
    for (std::pair<std::string, GLuint> map : shader.m_uMap)
        os << "\t" << map.first << " = " << map.second << std::endl;
    os << "]\n";
    return os;
  }

};


#endif
