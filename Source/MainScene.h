
/* -------------------------------------------------
  
 @Filename  : MainScene.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: The main state of the game. Its
			  the playable level

 ------------------------------------------------- */

#pragma once

#include "SceneInterface.h"
#include "SceneObjects.h"
#include "Scene.h"

class MainScene : public Scene
{ 
private:

	SceneInterface * m_pSceneInterface;	// HUD
	SceneObjects * m_pSceneObjects;		// Scene Objects
	
public:

	// Constructor & Deconstructor
	MainScene();
	~MainScene();

	// Member Functions
	void VOnRequest(SceneFactory *);
	void MousePress(int, int, int, int);
	void KeyPress(int, int);
	void Update();
	void Render();
};