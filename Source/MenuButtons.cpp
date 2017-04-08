
/* -------------------------------------------------
  
 @Filename  : MenuButtons.cpp
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: Class implementation.

 ------------------------------------------------- */

#include "MenuButtons.h"
#include "PlayEvent.h"

// Constructor & Deconstructor
MenuButtons::MenuButtons()
	: m_pRenderer(new GL_Renderer()),
	  m_PlayButton(new Button())
{
}

MenuButtons::~MenuButtons()
{
	SAFE_RELEASE(m_PlayButton);
	SAFE_RELEASE(m_pRenderer);
}

// Member Functions
void MenuButtons::VLoad() 
{
	m_PlayButton->SetPosition("Play", vec2(800, 200), vec2(200, 60));
	m_PlayButton->OnPress(new PlayEvent());
}

void MenuButtons::VUpdate()
{
	//m_pRenderer->Update();
}

void MenuButtons::VRender()
{
	m_pRenderer->RenderTexture(m_PlayButton->getTexture());
	m_pRenderer->RenderString(m_PlayButton->getString());
}

void MenuButtons::MousePress(int a, int b, int c, int d)
{
	m_PlayButton->MouseState(a, b, c, d);
}