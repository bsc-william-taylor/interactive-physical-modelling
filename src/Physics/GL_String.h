
/* -------------------------------------------------
  
 @Filename  : GL_String.h
 @author	: William Taylor
 @date		: 04/02/2014
 @purpose	: OpenGL class that can render 
			  text using the FreeType lib.

 ------------------------------------------------- */

#pragma once

#include "GL_Texture_Manager.h"
#include "GL_Texture.h"

class GL_String
{
private:

	tinyxml2::XMLDocument * m_Document;
	std::string m_Fontname;					
	std::string m_Text;						

	GL_Sprite * m_Sprite;
	GL_Object * m_Object;

	GLfloat m_Colour[4];
	GLuint m_Height;
	GLuint m_Width;
	GLuint m_VBO;
	GLuint m_VAO;

public:

	// Constructor & Deconstructor
	GL_String(std::string font = "", std::string tex = "");
	~GL_String();

	// Member Functions
	GLvoid Prepare();
    GLvoid PrepareFont(std::string fontname, std::string texture);

	// Set & Get Functions
	GLvoid setColour(GLfloat, GLfloat, GLfloat, GLfloat);
	GLvoid setParameters(GL_Object *);
	GLvoid setString(std::string);

	std::string getString();
	
	GL_Object * getObject();

	GLfloat * getColour(){ return m_Colour; }
	GLuint getStringLength();
	GLuint getVertexArray();
	GLuint getTextureID();
	GLuint getHeight();
	GLuint getWidth();
};