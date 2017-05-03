
/* -------------------------------------------------
  
 @Filename  : GL_Renderer.h
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: A renderer which draws objects
              and executes operations on all 
			  objects in a Scene.

 ------------------------------------------------- */

#pragma once

#include "GL_Texture.h"
#include "GL_String.h"

class GL_Renderer
{
private:

	vector<GL_Texture *> m_Textures;
	vector<GL_String *> m_Labels;
	// Previous View Variables
	vec2 a, b, c;

public:

	// Constructor & Deconstuctor
	GL_Renderer();	
	~GL_Renderer();
		
	// Member Functions
	GLvoid PushTexture(GL_Texture *);
	GLvoid PushText(GL_String *);
	GLvoid Prepare();
	GLvoid onRender();

	GLvoid RenderTexture(GL_Texture *);
	GLvoid RenderString(GL_String *);
};