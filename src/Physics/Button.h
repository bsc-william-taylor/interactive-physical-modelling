
/* -------------------------------------------------
  
 @Filename  : Button.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A simple button object class

 ------------------------------------------------- */

#pragma once

#include "GL_Texture.h"
#include "GL_String.h"

#include "EventManager.h"
#include "IEvent.h"

class Button
{
private:

	GL_Object * m_pTextureObject;
	GL_Object * m_pTextObject;

	GL_Texture * m_pSprite;		// The texture
	GL_String * m_pString;

	IEvent * event;			// Event to be called when pressed

	std::string filename;
	vec2 m_Position;			// Position
	vec2 m_Size;				// Size

public:

	// Constructor & Deconstructor
	Button();
	~Button();

	// Member Functions
	void MouseState(int, int, int, int);
	void SetPosition(const std::string&, vec2, vec2);
	void SetTexture(const std::string&);
	void OnPress(IEvent *);

	// Get & Set Functions
	GL_Texture * getTexture();
	GL_String * getString();
};