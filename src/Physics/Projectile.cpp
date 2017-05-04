
/* -------------------------------------------------
  
 @Filename  : Projectile.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Projectile.h"

// Constructor & Deconstructor
Projectile::Projectile()
	: charTexture(new GL_Texture()),
	  m_pObject(new GL_Object())
{
	m_Mass = 1.0f;
	m_Offset = vec2(0.0f);
	m_Fired = false;
	size = vec3(1.0, 1.0, 1.0);
	m_bDragForce = true;
}

Projectile::~Projectile()
{
	SAFE_RELEASE(m_pObject);
	SAFE_RELEASE(charTexture);
}

// Member Functions
void Projectile::onUpdate()
{
	if ( position.y <= TARGETHEIGHT/4 )
	{
		return;
	}

	m_pObject->setIdentity();

	if(m_Fired)
	{		
		vec2 PreviousTranslate = m_pObject->getTranslate();
		
		vec2 DragForce;

		if (m_bDragForce)
		{
			// get dimension of the object
			vec4 dim = m_pObject->getDimensions();
			// calculate radius
			float radius = (dim.w - dim.y) / 2.0f ;
			// calculate area of the object
			float area = pi<float>() * radius * radius;

			// calculate the drag force
			DragForce.x = -0.5f * (DENSITY_AIR) * DRAG_COEFICIENT * m_Velocity.x * m_Velocity.x * area;
		}

		m_Velocity += DragForce + GRAVITY;

		position += m_Velocity;

		m_pObject->setTranslate( PreviousTranslate + m_Velocity );
	}
}

void Projectile::toggleDragForce()
{
	m_bDragForce = !m_bDragForce;
}

void Projectile::setSize(vec2 vec)
{
	m_pObject->setSize(vec);
	size = vec3(vec.x, vec.y, 1.0f);
}

void Projectile::Fire()
{
	m_Fired = true;
}

float Projectile::getMass()
{
	return m_Mass;
}

void Projectile::Reset(float angle)
{
	m_pObject->setIdentity();
	m_pObject->setTranslate(vec2(0, 0));

	float cannonLengthX = 90*cosf(glm::radians(angle));
	float cannonLengthY = 90*sinf(glm::radians(angle));
	
	float xComponent( FULCRUM_X - 10 + cannonLengthX );	// 10 is bomb radius seeing the fact the origin is not in the center
	float yComponent( FULCRUM_Y - 10 + cannonLengthY );	// bomb radius again
	
	position = vec2(xComponent,yComponent);
	m_Velocity = vec2(0);

	vec2 m_StartingAcceleration;

	m_StartingAcceleration.x = FORCE * cosf(glm::radians(angle))/m_Mass;
	m_StartingAcceleration.y = FORCE * sinf(glm::radians(angle))/m_Mass;

	m_Velocity += m_StartingAcceleration;

	Setup(position);
}

void Projectile::Setup(vec2 position)
{
	m_pObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pObject->setPosition(position);
	m_pObject->setSize(vec2(size));
	
	charTexture->setTexture("data/img/iron.png", GL_CLAMP_TO_EDGE);
	charTexture->setParameters(m_pObject);
	charTexture->Prepare();

	position = position;
	m_Start = position;

}

// Get & Set Functions
void Projectile::setOffset(vec2 vec)
{
	m_Offset = vec;
}

void Projectile::setMass(float mass)
{
	m_Mass = mass;
}

void Projectile::setVelocity(vec2 vec)
{
	m_StartVelocity = vec;
	m_Velocity = vec;
}

void Projectile::setPosition(vec2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
}

GL_Texture * Projectile::getSprite()
{
	return charTexture;
}

bool Projectile::hasFired()
{
	return m_Fired;
}