/**
* \file:  Texture.hpp
* \brief Decalaration of the class "Texture"
*/

#ifndef __TEXTURE__HPP
#define __TEXTURE__HPP

#include <iostream>
#include "Shader.hpp"
#include <vector>
#include <string>

class Texture
{
private: 
	FilePath m_path;   /*!< name of the Mesh */
	GLuint m_id;   /*!< name of the Mesh */
	std::unique_ptr<Image> m_image;   /*!< name of the Mesh */
	GLenum m_format;   /*!< name of the Mesh */
	const GLint* m_minFilter;   /*!< name of the Mesh */
	const GLint* m_maxFilter;   /*!< name of the Mesh */
	bool m_isLoaded;   /*!< name of the Mesh */
	unsigned int s_nbTexture;   /*!< name of the Mesh */

public:

	/**
	* \brief constructor of Texture 
	*/
	Texture();

	/**
	* \brief constructor of Texture using a Filepath
    * \param v : Filepath of the file with textures
	*/
	Texture(FilePath);

	/**
	* \brief constructor of Texture using a path, a maxFilter and a minFilter 
    * \param v : Filepath of the file, minFilter and maxFilter
	*/
	Texture(FilePath path, const GLint* min, const GLint* max);

	/**
	* \brief destructor of Texture
	*/
	~Texture();

	/**
	* \brief getter of the Image that we will draw with Texture
    * \return : the pointer that leads us to the Image
	*/
	std::unique_ptr<Image> getImage();

	/**
	* \brief method that binds the Texture 
	*/
	void bind();

	/**
	* \brief method that unbinds the Texture 
	*/
	void unbind();

	/**
	* \brief getter of the id of the Texture 
    * \return : the id of the texture 
	*/
	GLuint getId();
};