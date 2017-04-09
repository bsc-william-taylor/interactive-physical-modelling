
/* -------------------------------------------------
  
 @Filename  : MenuLabel.cpp
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "MenuLabels.h"

// Constructor & Deconstructor
MenuLabels::MenuLabels()
	: m_HeaderObject(new GL_Object()),
	  m_pRenderer(new GL_Renderer())
{
	m_pText = new GL_String("data/largeText.xml", "data/LargeText.png");

	for(int i = 0; i < 3; i++)
	{
		m_Banners[i] = new GL_String("data/LargeText.xml", "data/LargeText.png");
		m_Objects[i] = new GL_Object();
	}
}

MenuLabels::~MenuLabels()
{
	SAFE_RELEASE(m_pText);
}

// Member Functions
void MenuLabels::VLoad() 
{
	m_HeaderObject->setOrtho2D(vec4(0, 0, 800, 540));
    m_HeaderObject->setScale(vec3(0.5, 0.5, 0.5));
    m_HeaderObject->setPosition(vec2(100, 750));
	m_HeaderObject->setSize(vec2(53, 53));
    
	m_pText->setParameters(m_HeaderObject);
	m_pText->setString("Physics Demo Coursework");
	m_pText->Prepare();

	GLuint position = 300;
	std::string names[] = {
		"B00233705",
        "B00235610",
        "B00243868"
	};

	for(GLuint i = 0; i < 3; i++)
	{
		m_Objects[i]->setOrtho2D(vec4(0, 0, 800, 540));
		m_Objects[i]->setPosition(vec2(150, position));
        m_Objects[i]->setScale(vec3(0.35, 0.35, 0.35));
		m_Objects[i]->setSize(vec2(35, 35));

		m_Banners[i]->setParameters(m_Objects[i]);
		m_Banners[i]->setString(names[i]);
		m_Banners[i]->Prepare();
	
		position += 150;
	}

}

void MenuLabels::VUpdate()
{
	
}

void MenuLabels::VRender()
{
	for(GLuint i = 0; i < 3; i++)
	{
		m_pRenderer->RenderString(m_Banners[i]);
	}

	m_pRenderer->RenderString(m_pText);
}
