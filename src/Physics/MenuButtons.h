
/* -------------------------------------------------
  
 @Filename  : MenuButtons.h
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: Basically all the buttons in the
			  menu scene.

 ------------------------------------------------- */
#pragma once

#include "SceneList.h"
#include "GL_Texture.h"
#include "GL_Renderer.h"
#include "Button.h"

class MenuButtons : public ISceneList
{
private:

	GL_Renderer * m_pRenderer;		// Renderer for the button
	Button * m_PlayButton;			// The menu button

public:

	// Constructor & Deconstructor
	MenuButtons();
	~MenuButtons();

	// Member Functions
	void MousePress(int, int, int, int);
	void VUpdate() sealed;
	void VRender() sealed;
	void VLoad() sealed;
};