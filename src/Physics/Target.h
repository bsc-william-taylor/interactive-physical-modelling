
/* -------------------------------------------------
  
 @Filename  : Target.h
 @author	: Cristian Szabo
 @date		: 19/03/2014
 @purpose	: A clickable target on the screen

 ------------------------------------------------- */

#pragma once

#include "TextureGL.h"
#include "Main.h"

class Target
{
private:

	TextureGL * charTexture;			// The sprite for the object
	ObjectGL * m_pObject;

	float m_Mass;
	vec2 position;

	bool m_Click;

public:

	// Constructor & Deconstructor
	Target();
	~Target();

	// Member Functions
	void Setup(vec2);
	void onUpdate();
	void onMousePress(int, int, int, int);

	// Get & Set & Check functions.
	TextureGL * getSprite();
	vec2 getPosition() { return position; }
	ObjectGL* getObject() { return m_pObject; }

	void setMass(float);
	void setPosition(vec2);
};