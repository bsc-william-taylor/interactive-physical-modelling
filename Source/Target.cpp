
/* -------------------------------------------------
  
 @Filename  : Target.cpp
 @author	: Cristian Szabo
 @date		: 19/03/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Target.h"
#include "Win32Codes.h"

// Constructor & Deconstructor
Target::Target()
	: m_pSprite(new GL_Texture()),
	  m_pObject(new GL_Object())
{
	m_Mass = 20.0f;

	m_Click = false;
}

Target::~Target()
{
	SAFE_RELEASE(m_pObject);
	SAFE_RELEASE(m_pSprite);
}

// Member Functions
void Target::Update()
{
	if ( m_Click )
	{
		return;
	}

	if ( m_Position.y < -TARGETHEIGHT / 2 )
	{
		return;
	}

	if( m_Mass )
	{		
		vec2 Acceleration = GRAVITY * m_Mass;

		m_Position += Acceleration;

		m_pObject->setTranslate(Acceleration);
	}
}

void Target::Setup(vec2 position)
{
	m_pObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pObject->setPosition(position);
	m_pObject->setSize(vec2(TARGETWIDTH, TARGETHEIGHT));
	
	m_pSprite->setTexture("data/img/target.png", GL_CLAMP_TO_EDGE);
	m_pSprite->setParameters(m_pObject);
	m_pSprite->Prepare();

	m_Position = position;
}



void Target::MousePress(int button, int state, int x, int y)
{
	if ( button == MOUSE_1 && state == HOLDING )
	{
		m_Click = true;

		if ( x >= m_Position.x  && x <= (m_Position.x + TARGETWIDTH) )
		{
			if ( y >= m_Position.y && y <= (m_Position.y + TARGETHEIGHT) )
			{
				float y1 = (y - (m_Position.y + TARGETHEIGHT/2));
				float x1 = (x - (m_Position.x + TARGETWIDTH/2));

				m_pObject->setTranslate(vec2(x1, y1));

				m_Position.x += x1;
				m_Position.y += y1;
			}
		}
	}
	else
	{
		m_Click = false;
	}
}

void Target::setMass(float mass)
{
	m_Mass = mass;
}

void Target::setPosition(vec2 pos)
{
	m_Position = pos;
}

GL_Texture * Target::getSprite()
{
	return m_pSprite;
}
