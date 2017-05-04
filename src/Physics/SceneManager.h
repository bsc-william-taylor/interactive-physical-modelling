
#pragma once

#include "SceneFactory.h"
#include "Scene.h"
#include <vector>

class SceneManager
{
	unsigned int currentScene;		
	std::vector<Scene*> scenes;		
	static SceneManager* manager;	
	SceneFactory* factory;
public:
	SceneManager();
	~SceneManager();

    Scene* getCurrent();

	void enableFactory();
	void updateManager();
	void startFrom(unsigned int);	
	void switchTo(unsigned int);
	void pushState(Scene *);
	void previousScene();
	void nextScene();

	static SceneManager* get();	
};