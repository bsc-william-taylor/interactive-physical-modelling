
/* -------------------------------------------------
  
 @Filename  : MenuLabel.h
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: Basically all the text in the main
			  menu scene.

 ------------------------------------------------- */

#pragma once

#include "SceneList.h"
#include "GL_String.h"
#include "GL_Renderer.h"

class MenuLabels : public ISceneList
{
private:

	GL_Renderer * m_pRenderer;		// Renderer for the text

	GL_Object * m_HeaderObject;
	GL_Object * m_Objects[3];

	GL_String * m_Banners[3];			// 3 Banners
	GL_String * m_pText;				// Header Text

public:

	// Constructor & Deconstructor
	MenuLabels();
	~MenuLabels();

	// Member Functions
	void VUpdate() sealed;
	void VRender() sealed;
	void VLoad() sealed;
};