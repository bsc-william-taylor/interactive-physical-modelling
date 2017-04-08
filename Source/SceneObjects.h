
/* -------------------------------------------------
  
 @Filename  : SceneObjects.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: All the objects in the scene.

 ------------------------------------------------- */

#pragma once

#include "SceneFactory.h"
#include "Trajectory.h"
#include "SceneList.h"
#include "Renderer.h"
#include "Objects.h"

class SceneObjects : public ISceneList
{
private:

	GL_Texture * m_pBackground;		// The background
	Renderer * m_pRenderer;			// Our renderer
	Cannon * m_pCannon;				// The cannon
	Target* m_pTarget;
	vec2 m_Camera;
	bool m_Reload;

public:

	// Constructor & Deconstructor
	SceneObjects();
	~SceneObjects();

	// Member Functions
	void MousePress(int, int, int, int);
	void KeyPress(int, int);
	void VOnRequest(SceneFactory *);
	void VUpdate();
	void VRender();
	void VLoad();

	bool mustReload();
	Cannon* getCannon();
	Target* getTarget();
};