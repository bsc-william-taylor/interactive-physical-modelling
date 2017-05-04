
/* -------------------------------------------------
  
 @Filename  : Projectile.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A projectile fired by the cannon

 ------------------------------------------------- */

#pragma once

#include "TextureGL.h"
#include "Main.h"

class Projectile
{
private:

	TextureGL * charTexture;			// The sprite for the object
	ObjectGL * m_pObject;

	float m_Mass;				// Its mass	
	vec2 m_StartVelocity;			// Its Velocity
	vec2 m_Velocity;				// Its Velocity
	vec2 position;
	vec2 m_Offset;
	vec2 m_Start;
	vec3 size;
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
	TextureGL * getSprite();
	vec2 getPosition() { return position; }
	vec2 getStartPos() { return m_Start; }
	vec2 getVelocity() { return m_Velocity; }
	ObjectGL* getObject() { return m_pObject; }
	float getMass();

	void setMass(float);
	void setVelocity(vec2);
	void setPosition(vec2);
	void setOffset(vec2);
	void setSize(vec2);

	bool hasFired();
};