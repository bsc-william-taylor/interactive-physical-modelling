
/* -------------------------------------------------
  
 @Filename  : Button.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Button.h"
#include "Win32Codes.h"

// Constructor & Deconstructor
Button::Button()
	: m_pTextureObject(new GL_Object()),
	  m_pTextObject(new GL_Object()),
	  m_pSprite(new GL_Texture())
{
	m_pString = new GL_String("data/text.xml", "data/tinyText.png");
	filename = "data/img/button.png";
}

Button::~Button()
{
	SAFE_RELEASE(m_pTextureObject);
	SAFE_RELEASE(m_pTextObject);
	SAFE_RELEASE(m_pString);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pEvent);
}

// Member Functions
void Button::OnPress(IEvent * event)
{
	m_pEvent = event;
}

void Button::SetPosition(const std::string& name, vec2 position, vec2 size)
{
	m_pTextureObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pTextureObject->setPosition(position);
	m_pTextureObject->setSize(size);

	m_pSprite->setTexture(filename.c_str(), GL_CLAMP_TO_EDGE);
	m_pSprite->setParameters(m_pTextureObject);
	m_pSprite->Prepare();

	m_pTextObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pTextObject->setPosition(position);
	m_pTextObject->setSize(vec2(25, 25));

	m_pString->setParameters(m_pTextObject);
	m_pString->setString(name.c_str());
	m_pString->Prepare();

	GLuint Height = (int)size.y - m_pString->getHeight();
	GLuint Width = (int)size.x - m_pString->getWidth();

	m_pTextObject->setTranslate(vec2(Width/2, Height/2));
	m_Position = position;
	m_Size = size;
}

void Button::SetTexture(const std::string& file)
{
	filename = file;
}

void Button::MouseState(int Key, int State, int x, int y)
{
	if(x >= m_Position.x && x <= m_Position.x + m_Size.x && y >= m_Position.y && y <= m_Position.y + m_Size.y)
	{
		if(Key == MOUSE_1 && State == RELEASED)
		{
			EventManager::get()->TriggerEvent(m_pEvent, false, this);
		}
	}
}

// Get & Set Functions
GL_Texture * Button::getTexture()
{
	return m_pSprite;
}

GL_String * Button::getString()
{
	return m_pString;
}