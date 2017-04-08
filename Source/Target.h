
/* -------------------------------------------------
  
 @Filename  : Target.h
 @author	: Cristian Szabo
 @date		: 19/03/2014
 @purpose	: A clickable target on the screen

 ------------------------------------------------- */

#pragma once

#include "GL_Texture.h"
#include "Globals.h"

class Target
{
private:

	GL_Texture * m_pSprite;			// The sprite for the object
	GL_Object * m_pObject;

	float m_Mass;
	vec2 m_Position;

	bool m_Click;

public:

	// Constructor & Deconstructor
	Target();
	~Target();

	// Member Functions
	void Setup(vec2);
	void Update();
	void MousePress(int, int, int, int);

	// Get & Set & Check functions.
	GL_Texture * getSprite();
	vec2 getPosition() { return m_Position; }
	GL_Object* getObject() { return m_pObject; }

	void setMass(float);
	void setPosition(vec2);
};