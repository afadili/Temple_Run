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
#include <GL/glew.h>
#include <SDL/SDL.h>

class Texture
{
private: 
	FilePath m_path;   /*!< Path of the file of the texture */
	GLuint m_id;   /*!< id of the texture */
	std::unique_ptr<Image> m_image;   /*!< Ipointer to the image of the texture */
	GLenum m_format;   /*!< format of the texture */
	const GLint* m_minFilter;   /*!< minimum filter of the texture */
	const GLint* m_maxFilter;   /*!< maximum filter of the texture  */
	bool m_isLoaded;   /*!< boolean to know is the texture is loaded or not */
	unsigned int s_nbTexture;   /*!< number of textures*/

public:

	/**
	* \brief constructor of Texture 
	*/
	Texture() = default;

	/**
	* \brief method that loads the texture 
	*/
	loadTexture(std::string Filepath);

	/**
	* \brief constructor of Texture using a Filepath
    * \param v : Filepath of the file with textures
	*/
	Texture(std::string FilePath);

	/**
	* \brief constructor of Texture using a path, a maxFilter and a minFilter 
    * \param v : Filepath of the file, minFilter and maxFilter
	*/
	Texture(FilePath path, const GLint* min, const GLint* max);

	/**
	* \brief destructor of Texture
	*/
	~Texture(){};

	/**
	* \brief getter of the Image that we will draw with Texture
    * \return : the pointer that leads us to the Image
	*/
	std::unique_ptr<Image> getImage(); // pas besoin car la methode loadImage existe déjà dans glimac et on peut l'utiliser

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

	/**
	* \brief methods that free the memory allocated to the texture after using it
	*/
	void free();
};