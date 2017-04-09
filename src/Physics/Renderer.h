
/* -------------------------------------------------
  
 @Filename  : Renderer.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A renderer class responsible for 
			  rendering each object.

 ------------------------------------------------- */

#pragma once

#include "GL_Renderer.h"
#include "GL_Texture.h" 
#include "Cannon.h"
#include "Target.h"

class Renderer
{
private:

	// GL renderer for drawing gl objects (eg GL_Image)
	GL_Renderer * m_pRenderer;

public:

	// Constructor & Deconstructor
	Renderer();
	~Renderer();

	// Member Functions
	void RenderBackground(GL_Texture *);
	void RenderCannon(Cannon *);
	void RenderTarget(Target*);
};