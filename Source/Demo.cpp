
/* -------------------------------------------------
  
 @Filename  : Demo.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: class implementation

 ------------------------------------------------- */

#include "GL_Texture_Manager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Demo.h"

Demo::Demo()
	: m_pSystem(new Win32System()),
	  m_pTimer(new Win32Timer()),
	  m_Framerate(60)
{
	SetConsoleTitle("Debug Console");
}

Demo::~Demo()
{
	// Delete GL Managers here
	RELEASE_MANAGER(GL_TextureManager::get());
	RELEASE_MANAGER(GL_Shader_Manager::get());
	
	// Delete Managers
	RELEASE_MANAGER(SceneManager::get());
	RELEASE_MANAGER(EventManager::get());

	// Release Resources
	SAFE_RELEASE(m_pSystem);
	SAFE_RELEASE(m_pTimer);
}

void Demo::SetupWindow()
{
	Window::SIZES WindowSizes;

	WindowSizes.w = 1280;
	WindowSizes.h = 720;
	WindowSizes.x = 0;
	WindowSizes.y = 0;

	m_pSystem->setWindowTraits("Physics Demo", WindowSizes);
	m_pSystem->setWindowType(Win32Window::WINDOWED);
	m_pSystem->Initialise();
}

void Demo::SetupStates()
{
	auto SceneManager = SceneManager::get();

	SceneManager->PushState(new MainMenu());
	SceneManager->PushState(new MainScene());
	SceneManager->StartFrom(MAIN_MENU);
	SceneManager->EnableFactory();
}

void Demo::setFrameRate(UINT framerate)
{
	m_Framerate = framerate;
}

void Demo::Execute()
{
	m_pTimer = new Win32Timer();
	m_pTimer->Start();

	SetupWindow();
	SetupStates();

	auto Events = EventManager::get();
	auto Scenes = SceneManager::get();
	
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Main Game Loop
	while(m_pSystem->WindowRunning()) 
	{		
		glClear( GL_COLOR_BUFFER_BIT );

		m_pSystem->Update();

		Events->UpdateManager();
		Scenes->UpdateManager();

		m_pSystem->SwapWindowBuffers();
	
		float timeLeft = 0;
		// Frame Limiting :P 
		while(timeLeft < (double)1.0e9/m_Framerate)
		{
			m_pTimer->Stop();
			timeLeft = m_pTimer->Difference(TimeType::NS);
		}

		m_pTimer->Start();
	}
}