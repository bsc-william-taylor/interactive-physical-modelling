
/* -------------------------------------------------
  
 @Filename  : GL_Program.h
 @purpose	: Main Definition
 @author	: William Taylor
 @date		: 04/02/2014

 ------------------------------------------------- */

#pragma once

#include "GL_Header.h"

class GL_Program 
{
private:

	std::string VertexFilename;
	std::string FragFilename;

	GLuint Shaders[2];	// Array for storing shader ID's.
	GLuint Program;		// ID for the current program.

public:

	// Simple ENUM so the user can load each shader easily.
	enum Types { VERTEX_SHADER,	FRAG_SHADER, };

public:

	// Constructor & Deconstructor
	GL_Program();
	~GL_Program();

	// Member Functions
	GLvoid Load(Types, const std::string&);
	GLvoid OutputLog(Types);
	GLvoid Release();
	GLvoid Create();
	GLvoid Link();
	GLvoid Use();

	// Set Functions
	GLvoid setMatrix(const std::string&, glm::mat4);
	GLvoid setTexture(GLuint);

	// Get Functions
	GLuint getAttribute(const std::string&);
	GLuint getUniform(const std::string&);

	const std::string& getFS();
	const std::string& getVS();

private:

	// private read function file
	std::string ReadFile(const std::string&);
};

typedef GL_Program Shader;