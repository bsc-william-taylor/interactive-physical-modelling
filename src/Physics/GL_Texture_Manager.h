
/* -------------------------------------------------
  
 @Filename  : GL_Texture_Manager.h
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: A texture manager for opengl needs
              a lot of work done.

 ------------------------------------------------- */

#pragma once

#include "GL_Header.h"

struct GL_Sprite
{
	vector<RGBQUAD> Colour;
	std::string m_TextureName;
	GLuint Height;
	GLuint Width;
	GLuint m_ID;

	~GL_Sprite() { glDeleteTextures(1, &m_ID); }
};

struct GL_Colour
{
	RGBQUAD Colour;
	GLfloat x;
	GLfloat y;
};

class TextureManagerGL
{
private:

	static TextureManagerGL * manager;		// Singletons Instance
	vector<GL_Sprite *> m_Textures;				// Store all textures created for memory checking

public:

	// Deconstructor
	~TextureManagerGL();

	static TextureManagerGL * get();			// Static get function for accessing the class

	// Member Functions
	GL_Sprite * CreateTexture(GLubyte *, GLuint, GLuint, GLenum);
	GL_Sprite * CreateTexture(const std::string&, GLenum);

	GLvoid FreeTextures();

	GLuint getTextureCount();

private:

	// Constructor
	TextureManagerGL();

	GL_Sprite * LoadTexture(const std::string&, GLenum e);
};

// Helps Reduce line length
typedef TextureManagerGL GL_Textures;