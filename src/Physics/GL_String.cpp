
/* -------------------------------------------------
  
 @Filename  : GL_String.cpp
 @author	: William Taylor
 @date		: 14/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "GL_String.h"

// Constructor & Deconstructor
GL_String::GL_String(std::string fontname, std::string texture)
	: m_Object(NULL)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindVertexArray(0);

	m_Document = new tinyxml2::XMLDocument();
	m_Document->LoadFile(fontname.c_str());
	m_Fontname = fontname;

	m_Sprite = GL_TextureManager::get()->CreateTexture(texture, GL_CLAMP_TO_EDGE);

	setColour(0, 0, 0, 1);
}

GL_String::~GL_String()
{
	glDeleteVertexArrays(1, &m_VBO);
	glDeleteBuffers(1, &m_VBO);
}

GLvoid GL_String::setParameters(GL_Object * object)
{
	m_Object = object;
}

GLvoid GL_String::Prepare()
{
	GLchar * vs = "data/shaders/text.vert";
	GLchar * fs = "data/shaders/text.frag";

	m_Object->setShaders(vs, fs);
}

void GL_String::setString(std::string text)
{
	if(!text.empty())
	{
		vec2 position = m_Object->getPosition();

		std::vector<vec4> positions;

		positions.reserve(text.size() * 4);
		m_Height = 0;
		m_Width = 0;

		tinyxml2::XMLElement * start =  m_Document->FirstChildElement("fontMetrics")->FirstChildElement("character");
		
		for(int i = 0; i < text.size(); i++)
		{
			tinyxml2::XMLElement * element =  start;

			for(int b = 0; b < (int)text[i] - 32; b++)
			{
				element = element->NextSiblingElement();
			}

			GLfloat x = atoi(element->FirstChildElement("x")->GetText());
			GLfloat w = atoi(element->FirstChildElement("width")->GetText());
			GLfloat y = m_Sprite->Height - atoi(element->FirstChildElement("y")->GetText());
			GLfloat h = atoi(element->FirstChildElement("height")->GetText());
			GLfloat realX = (GLfloat)x/m_Sprite->Width;
		    GLfloat realY = (GLfloat)y/m_Sprite->Height;
		    GLfloat realW = (GLfloat)(x + w)/m_Sprite->Width;
		    GLfloat realH = (GLfloat)(y - h)/m_Sprite->Height;
			
			positions.push_back(vec4(position,					vec2(realX, realH)));					
			positions.push_back(vec4(position + vec2(0, h),		vec2(realX, realY)));
			positions.push_back(vec4(position + vec2(w, 0),		vec2(realW, realH)));
			positions.push_back(vec4(position + vec2(w, h),		vec2(realW, realY)));
			
			m_Height += h;
			m_Width += w;

			position += vec2(w, 0);
		}

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * positions.size(), &positions[0], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glBindVertexArray(0);

		m_Height /= text.size();
		m_Text = text;
	}
}

GLvoid GL_String::setColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_Colour[0] = r;
	m_Colour[1] = g;
	m_Colour[2] = b;
	m_Colour[3] = a;
}

GLuint GL_String::getHeight()
{
	return(m_Height);
}

GLuint GL_String::getWidth()
{
	return(m_Width);
}

GLuint GL_String::getTextureID()
{
	return m_Sprite->m_ID;
}

GLuint GL_String::getStringLength()
{
	return(m_Text.size() * 4);
}

GLuint GL_String::getVertexArray()
{
	return m_VAO;
}

GL_Object * GL_String::getObject() 
{ 
	return m_Object; 
}

std::string GL_String::getString()
{
	return m_Text;
}