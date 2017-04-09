
/* -------------------------------------------------
  
 @Filename  : MenuImages.h
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: Basically all the images in the
			  menu scene.

 ------------------------------------------------- */

#pragma once

#include "SceneList.h"
#include "GL_Texture.h"
#include "GL_Renderer.h"

class MenuImages : public ISceneList
{
private:

	GL_Renderer * m_pRenderer;			// Renderer for the images.
	GL_Texture * m_pBackground;			// the background
	GL_Object * m_pBgObject;

public:

	// Constructor & Deconstructor
	MenuImages();
	~MenuImages();

	// Member Functions
	void VUpdate() sealed;
	void VRender() sealed;
	void VLoad() sealed;

	// Get Functions
	GL_Texture * getBackground();
};