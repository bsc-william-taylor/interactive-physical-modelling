
/* -------------------------------------------------
  
 @Filename  : GL_Texture.cpp
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "GL_Texture.h"
#include "GL_Texture_Manager.h"

// Constructor & Deconstructor
GL_Texture::GL_Texture()
{	
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindVertexArray(0);
}

GL_Texture::~GL_Texture()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

// Member Functions
void GL_Texture::Prepare() 
{
	vec4 p = m_Object->getDimensions();

	GLchar * vs = "data/shaders/texture.vert";
	GLchar * fs = "data/shaders/texture.frag";
	
	GLfloat data[] = {
		p.x, p.y, 0, 0,
		p.x, p.w, 0, 1,
		p.z, p.y, 1, 0,
		p.z, p.w, 1, 1
	};

	
	m_Texture = GL_Textures::get()->CreateTexture(m_Filename, m_Setting);
	m_Object->setShaders(vs, fs);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * 16, &data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

GLvoid GL_Texture::setID(GLuint ID)
{
	m_Texture->m_ID = ID;
}

GLvoid GL_Texture::setParameters(GL_Object * object)
{
	m_Object = object;
}

// Get & Set Functions
void GL_Texture::setTexture(std::string filename, GLenum e)
{
	m_Filename = filename;
	m_Setting = e;
}

GL_Object * GL_Texture::getObject()
{
	return m_Object;
}

GLuint GL_Texture::getTextureID()
{
	return m_Texture->m_ID;
}

const std::string& GL_Texture::getPath()
{
	return m_Filename;
}

GLuint GL_Texture::getVAO()
{
	return m_VAO;
}