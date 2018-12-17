/**
* \file Program.hpp
* \brief Declaration of class "Program"
*/

#ifndef __PROGRAM__HPP
#define __PROGRAM__HPP

#include <GL/glew.h>
#include "Shader.hpp"
#include "FilePath.hpp"

namespace glimac {

class Program {
public:
	/**
	* \brief constructor of Program 
	*/
	//Program(): m_nGLId(glCreateProgram()) {
	//}

	/**
	* \brief destructor of Program
	*/
	~Program() {
		glDeleteProgram(m_nGLId);
	}

    /**
	* \brief constructor of Program
	* \param 
	*/
	Program(Program&& rvalue): m_nGLId(rvalue.m_nGLId) {
		rvalue.m_nGLId = 0;
	}

	/**
	* \brief perator overload of "="
	*/
	Program& operator =(Program&& rvalue) {
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	/**
	* \brief getter of program's Id
	*/
	GLuint getGLId() const {
		return m_nGLId;
	}

	/**
	* \brief method of Program that attach shader 
	*/
	void attachShader(const Shader& shader) {
		glAttachShader(m_nGLId, shader.getGLId());
	}

	/**
	* \brief method that links the Program
	*/
	bool link();

	/**
	* \brief getter of infos
	*/
	const std::string getInfoLog() const;

	/**
	* \brief setter to use the Program
	*/
	void use() const {
		glUseProgram(m_nGLId);
	}

private:
	/**
	* \brief constructor of program using a reference
	*/
	Program(const Program&);

	/**
	* \brief operator overload of "="
	*/
	Program& operator =(const Program&);

	GLuint m_nGLId;  /*!< Id of the Program */
};

// Build a GLSL program from source code
Program buildProgram(const GLchar* vsSrc, const GLchar* fsSrc);

// Load source code from files and build a GLSL program
Program loadProgram(const FilePath& vsFile, const FilePath& fsFile);


}

#endif