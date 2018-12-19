#include <Render/ShaderManager.hpp>

ShaderManager::ShaderManager(const glimac::FilePath &vs, const glimac::FilePath &fs)
: m_vsPath(vs), m_fsPath(fs), m_program(glimac::loadProgram(vs, fs)){
}

void ShaderManager::addUniform(const std::string &name) {
  GLint uVar = glGetUniformLocation(id(), name.c_str());
  m_uMap.insert(std::pair<std::string, GLint>(name, uVar));
}

void ShaderManager::sendUniformMatrix4fv(std::string name, glm::mat4 value) {
  glUniformMatrix4fv(m_uMap[name], 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderManager::sendUniform3f(std::string name, glm::vec3 value) {
  glUniform3f(m_uMap[name], value.x, value.y, value.z);
}

void ShaderManager::sendUniform1i(std::string name, int num) {
  glUniform1i(m_uMap[name], num);
}

void ShaderManager::sendUniform1f(std::string name, float num) {
  glUniform1f(m_uMap[name], num);
}

void ShaderManager::use() {
  m_program.use();
}
