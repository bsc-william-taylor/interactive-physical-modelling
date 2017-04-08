
/* -------------------------------------------------
  
 @Filename  : SceneManager.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A singletone which manages scenes
			  in the applications.

 ------------------------------------------------- */

#pragma once

#include "SceneFactory.h"
#include "Scene.h"
#include <vector>

class SceneManager
{
private:

	unsigned int m_CurrentPlace;		// Current scene to render
	std::vector<Scene *> m_vScenes;		// All scenes available
	static SceneManager * m_pManager;	// Singleton instance
	SceneFactory * m_pFactory;


public:

	// Constructor & Deconstructor
	SceneManager();
	~SceneManager();

	// Member functions
	void EnableFactory();
	void UpdateManager();
	void StartFrom(unsigned int);	
	void SwitchTo(unsigned int);
	void PushState(Scene *);
	void PreviousScene();
	void NextScene();

	// Get & Set Functions
	static SceneManager * get();		// Singleton get function
	Scene * getCurrent();
};