
/* -------------------------------------------------
  
 @Filename  : GL_Texture.h
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Simple GL_Texture object that sets up 
			  a texture, it can be drawn using the 
			  draw texture method in the GL_Renderer 
			  Class.

 ------------------------------------------------- */

#pragma once

#include "GL_Texture_Manager.h"
#include "GL_Shader_Manager.h"
#include "GL_Object.h"

class GL_Texture
{
private:

	std::string path;			// Filename

	GL_Sprite * m_Texture;			// Ref to Sprite (Custom Data type def in GL_Texture_Manager
	GL_Object * m_Object;

	GLenum m_Setting;			
	GLuint m_VAO;
	GLuint m_VBO;
		
public:

	// Constructor & Deconstructor
	GL_Texture();
	~GL_Texture();

	// Member Functions
	GLvoid Prepare();

	// Get & Set Function
	GLvoid setParameters(GL_Object *);
	GLvoid setTexture(std::string, GLenum);
	GLvoid setID(GLuint);

	GL_Object * getObject();

	const std::string& getPath();
	GLuint getTextureID();
	GLuint getVAO();
};
