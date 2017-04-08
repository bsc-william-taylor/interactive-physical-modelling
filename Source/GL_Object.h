
/* -------------------------------------------------
  
 @Filename  : GL_Object.h
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Base Class for all drawable
			  opengl objects makes classes
			  more compact and easier to use.

 ------------------------------------------------- */

#pragma once

#include "GL_Program.h"
#include "GL_Matrix.h"

class GL_Object
{
private:

	GL_Program * m_pShader;			// OpenGL Shader Program
	GL_Matrix * m_Matrix;			// Matrix

	vec4 m_Positions;
	vec2 m_Translate;
	vec4 m_Rotation;

public:
	
	// Constructor & Deconstructor
	GL_Object();
	~GL_Object();

	// Methods can be override if needed.
	GLvoid setShaders(GLchar *, GLchar *);
	GLvoid setRotation(GLfloat, vec3);
	GLvoid sendMatricesToShader();
	GLvoid setIdentity();
	GLvoid setTranslate(vec2);
	GLvoid setPosition(vec2);
	GLvoid setOrtho2D(vec4);
	GLvoid setScale(vec3);
	GLvoid setSize(vec2);

	vec4 getDimensions();
	vec2 getTranslate();
	vec2 getPosition();

	GLvoid BindProgram();
	GLvoid EndProgram();

	GL_Program* getShader() { return m_pShader; }
	GL_Matrix* getMatrix() { return m_Matrix; }
};