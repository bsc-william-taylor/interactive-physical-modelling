
/* -------------------------------------------------
  
 @Filename  : MainMenu.cpp
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: The main menu scene obviously :P

 ------------------------------------------------- */

#include "EventManager.h"
#include "Win32Codes.h"
#include "ExitEvent.h"
#include "MainMenu.h"

// Constructor & Deconstructor
MainMenu::MainMenu()
	: m_pButtons(new MenuButtons()),
	  m_pImages(new MenuImages()),
	  m_pLabels(new MenuLabels())
{
	glViewport(0, 0, 1280, 720);

	m_pImages->VLoad();
	m_pLabels->VLoad();
	m_pButtons->VLoad();
}

MainMenu::~MainMenu()
{
	SAFE_RELEASE(m_pButtons);
	SAFE_RELEASE(m_pImages);
	SAFE_RELEASE(m_pLabels);
}

// Member Functions
void MainMenu::Update()
{
	m_pButtons->VUpdate();
	m_pLabels->VUpdate();
	m_pImages->VUpdate();
}

void MainMenu::Render()
{
	m_pImages->VRender();
	m_pButtons->VRender();
	m_pLabels->VRender();
}

void MainMenu::KeyPress(int Key, int State)
{
	if(KEY_DOWN(ESCAPE, Key, State))
	{
		EventManager::get()->TriggerEvent(new ExitEvent(), true, this);
	}
}

void MainMenu::MousePress(int Key, int State, int x, int y)
{
	m_pButtons->MousePress(Key, State, x, y);
}

void MainMenu::VOnCommit(SceneFactory * Factory)
{
	Factory->PushAsset("MenuBackground", m_pImages->getBackground());
}
