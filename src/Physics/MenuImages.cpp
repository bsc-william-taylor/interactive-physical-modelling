
/* -------------------------------------------------
  
 @Filename  : MenuImages.cpp
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "MenuImages.h"

// Constructor & Deconstructor
MenuImages::MenuImages()
	: m_pBackground(new GL_Texture()),
	  m_pRenderer(new GL_Renderer()),
	  m_pBgObject(new GL_Object())
{
}

MenuImages::~MenuImages()
{
	SAFE_RELEASE(m_pBackground);
	SAFE_RELEASE(m_pRenderer);
}

// Member Functions
void MenuImages::VLoad()
{
	m_pBgObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pBgObject->setPosition(vec2(0, 0));
	m_pBgObject->setSize(vec2(3000, 1383));

	m_pBackground->setTexture("data/img/background.png", GL_CLAMP_TO_EDGE);
	m_pBackground->setParameters(m_pBgObject);
	m_pBackground->Prepare();
}

void MenuImages::VUpdate()
{
}

void MenuImages::VRender()
{
	m_pRenderer->RenderTexture(m_pBackground);
}

GL_Texture * MenuImages::getBackground()
{
	return this->m_pBackground;
}
