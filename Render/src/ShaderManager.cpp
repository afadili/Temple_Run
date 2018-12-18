#include <Render/ShaderManager.hpp>


ShaderManager::ShaderManager(glimac::FilePath &vs, glimac::FilePath &fs)
		: m_vsPath(vs), m_fsPath(fs) {
	m_program = loadProgram(m_vsPath, m_fsPath);
}

void ShaderManager::addUniform(std::string name){
    m_uMap.insert( std::pair<std::string,GLuint>(name , glGetUniformLocation(m_program.getGLId(), name.c_str())));
}

void ShaderManager::sendUniformMatrix4fv(std::string name, glm::mat4 value){
    glUniformMatrix4fv(m_uMap[name], 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderManager::sendUniform3f(std::string name, glm::vec3 value){
    glUniform3f(m_uMap[name], value.x, value.y, value.z);
}

void ShaderManager::sendUniform1i(GLuint value, int num){
    glUniform1i(value, num);
}

void ShaderManager::sendUniform1f(std::string name, float num){
    glUniform1f(m_uMap[name], num);
}

void ShaderManager::use(){
    m_program.use();
}

GLuint ShaderManager::getGLId() const {
	return m_nGLId;
}