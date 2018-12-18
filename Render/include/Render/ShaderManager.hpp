/**
* \file ShaderManager.hpp
* \brief description : Declaration of the class "ShaderManager"
*/

#ifndef __SHADERMANAGER__HPP
#define __SHADERMANAGER__HPP

#include <GL/glew.h>
#include <string>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <map>
#include <glimac/Program.hpp>


class ShaderManager {
private:
	glimac::Program m_program;
	glimac::FilePath m_vsPath;
	glimac::FilePath m_fsPath;
	std::map<std::string, GLuint> m_uMap;

public:
	GLuint m_nGLId;

	/**
	* \brief constructor of Shader
	*/
	ShaderManager() = default;

	/**
	* \brief constructor of Shader
    * \param vs : filepath of the vs file
    * \param fs : filepath of the fs file
	*/
	ShaderManager(glimac::FilePath &vs, glimac::FilePath &fs);

	/**
	* \brief destructor of Shader
	*/
	~ShaderManager();


	/**
	* \brief 
	* \param name :
	*/
	void addUniform(std::string name);

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
    void sendUniform1i(GLuint value, int num);

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

	GLuint getGLId() const;
};


#endif
