
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
	: charTexture(new TextureGL()),
	  m_pObject(new ObjectGL())
{
	m_Mass = 20.0f;

	m_Click = false;
}

Target::~Target()
{
	SAFE_RELEASE(m_pObject);
	SAFE_RELEASE(charTexture);
}

// Member Functions
void Target::onUpdate()
{
	if ( m_Click )
	{
		return;
	}

	if ( position.y - 10 < -TARGETHEIGHT / 2 )
	{
		return;
	}

	if( m_Mass )
	{		
		vec2 Acceleration = GRAVITY * m_Mass;

		position += Acceleration;

		m_pObject->setTranslate(Acceleration);
	}
}

void Target::Setup(vec2 position)
{
	m_pObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pObject->setPosition(position);
	m_pObject->setSize(vec2(TARGETWIDTH, TARGETHEIGHT));
	
	charTexture->setTexture("data/img/target.png", GL_CLAMP_TO_EDGE);
	charTexture->setParameters(m_pObject);
	charTexture->prepare();

	this->position = position;
}



void Target::onMousePress(int button, int state, int x, int y)
{
	if ( button == MOUSE_1 && state == HOLDING )
	{
		m_Click = true;

		if ( x >= position.x  && x <= (position.x + TARGETWIDTH) )
		{
			if ( y >= position.y && y <= (position.y + TARGETHEIGHT) )
			{
				float y1 = (y - (position.y + TARGETHEIGHT/2));
				float x1 = (x - (position.x + TARGETWIDTH/2));

				m_pObject->setTranslate(vec2(x1, y1));

				position.x += x1;
				position.y += y1;
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
	position = pos;
}

TextureGL * Target::getSprite()
{
	return charTexture;
}
