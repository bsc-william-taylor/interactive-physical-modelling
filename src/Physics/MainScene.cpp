
/* -------------------------------------------------
  
 @Filename  : MainScene.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: The main state of the game. Its
			  the playable level

 ------------------------------------------------- */

#include "EventManager.h"
#include "Win32Codes.h"
#include "MainScene.h"
#include "BackEvent.h"

// Constructor & Deconstructor
MainScene::MainScene()
	: m_pSceneInterface(new SceneInterface()),
	  m_pSceneObjects(new SceneObjects())
{
	glViewport(0, 0, 1280, 720);

	m_pSceneInterface->GiveObjects(m_pSceneObjects);
	m_pSceneInterface->VLoad();
	m_pSceneObjects->VLoad();
}

MainScene::~MainScene()
{
	SAFE_RELEASE(m_pSceneObjects);
}

// Member Functions
void MainScene::VOnRequest(SceneFactory * Factory)
{
	m_pSceneObjects->VOnRequest(Factory);
}

void MainScene::KeyPress(int Key, int State)
{
	if(KEY_DOWN(ESCAPE, Key, State))
	{
		EventManager::get()->TriggerEvent(new BackEvent(), true, this);
	}
	else 
	{
		m_pSceneObjects->KeyPress(Key, State);
	}
}

void MainScene::MousePress(int button, int state, int x, int y)
{
	m_pSceneInterface->MousePress(button, state, x, y);
	m_pSceneObjects->MousePress(button, state, x, y);
}

void MainScene::Update()
{
	m_pSceneObjects->VUpdate();
	m_pSceneInterface->VUpdate();
}

void MainScene::Render()
{
	m_pSceneObjects->VRender();
	m_pSceneInterface->VRender();
}