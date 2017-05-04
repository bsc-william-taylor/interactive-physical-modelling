
/* -------------------------------------------------
  
 @Filename  : Target.h
 @author	: Cristian Szabo
 @date		: 19/03/2014
 @purpose	: A clickable target on the screen

 ------------------------------------------------- */

#pragma once

#include "GL_Texture.h"
#include "Main.h"

class Target
{
private:

	GL_Texture * charTexture;			// The sprite for the object
	GL_Object * m_pObject;

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
	GL_Texture * getSprite();
	vec2 getPosition() { return position; }
	GL_Object* getObject() { return m_pObject; }

	void setMass(float);
	void setPosition(vec2);
};