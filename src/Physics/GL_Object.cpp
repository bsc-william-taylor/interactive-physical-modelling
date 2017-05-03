
/* -------------------------------------------------
  
 @Filename  : GL_Object.h
 @author	: William Taylor
 @date		: 14/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "GL_Shader_Manager.h"
#include "GL_Object.h"

// Constructor
GL_Object::GL_Object() 
	: m_Matrix(new GL_Matrix()),
	  m_pShader(NULL)
{
}

GL_Object::~GL_Object()
{
	SAFE_RELEASE(m_Matrix);
}

// Methods can be override if needed.
GLvoid GL_Object::setShaders(GLchar * vs, GLchar * fs)
{
	m_pShader = ShaderManagerGL::get()->GetShader(vs, fs);
}

vec2 GL_Object::getPosition()
{
	return vec2(m_Positions.x, m_Positions.y);
}

GLvoid GL_Object::sendMatricesToShader()
{
	m_pShader->setMatrix("Projection", m_Matrix->getProjection());
	m_pShader->setMatrix("Model", m_Matrix->getModel());
	m_pShader->setMatrix("View", m_Matrix->getView());
}

GLvoid GL_Object::setRotation(GLfloat angle, vec3 vec)
{
	m_Rotation.w = angle;

	m_Rotation.x = vec.x;
	m_Rotation.y = vec.y;
	m_Rotation.z = vec.z;

	m_Matrix->Rotate(angle, vec);
}

GLvoid GL_Object::BindProgram()
{
	m_pShader->Use();
}

GLvoid GL_Object::setTranslate(vec2 vec)
{
	m_Translate = vec;
	m_Matrix->Translate(vec3(vec, 0.0));
}

GLvoid GL_Object::EndProgram()
{
	m_pShader->Release();
}

GLvoid GL_Object::setPosition(vec2 vec)
{
	m_Positions.x = vec.x;
	m_Positions.y = vec.y;
}

GLvoid GL_Object::setSize(vec2 vec)
{
	m_Positions.z = m_Positions.x + vec.x;
	m_Positions.w = m_Positions.y + vec.y;
}

GLvoid GL_Object::setScale(vec3 vec)
{
	m_Matrix->Scale(vec);
}

GLvoid GL_Object::setOrtho2D(vec4 v)
{
	m_Matrix->Ortho(vec2(v.x, v.z), vec2(v.y, v.w));
}

GLvoid GL_Object::setIdentity()
{
	m_Matrix->LoadIdenditity();
}

vec4 GL_Object::getDimensions()
{
	return(m_Positions);
}

vec2 GL_Object::getTranslate()
{
	return(m_Translate);
}