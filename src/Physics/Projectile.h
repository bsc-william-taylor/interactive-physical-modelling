
/* -------------------------------------------------
  
 @Filename  : Projectile.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A projectile fired by the cannon

 ------------------------------------------------- */

#pragma once

#include "GL_Texture.h"
#include "Main.h"

class Projectile
{
private:

	GL_Texture * m_pSprite;			// The sprite for the object
	GL_Object * m_pObject;

	float m_Mass;				// Its mass	
	vec2 m_StartVelocity;			// Its Velocity
	vec2 m_Velocity;				// Its Velocity
	vec2 m_Position;
	vec2 m_Offset;
	vec2 m_Start;
	vec3 m_Size;
	bool m_Fired;					// Has it been fired ?
	bool m_bDragForce;

public:

	// Constructor & Deconstructor
	Projectile();
	~Projectile();

	// Member Functions
	void Setup(vec2);
	void onUpdate();
	void Reset(float angle);
	void Fire();
	void toggleDragForce();

	// Get & Set & Check functions.
	GL_Texture * getSprite();
	vec2 getPosition() { return m_Position; }
	vec2 getStartPos() { return m_Start; }
	vec2 getVelocity() { return m_Velocity; }
	GL_Object* getObject() { return m_pObject; }
	float getMass();

	void setMass(float);
	void setVelocity(vec2);
	void setPosition(vec2);
	void setOffset(vec2);
	void setSize(vec2);

	bool hasFired();
};