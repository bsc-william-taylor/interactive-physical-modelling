
/* -------------------------------------------------
  
 @Filename  : Trajectory.h
 @author	: William Taylor
 @date		: 27/02/2014
 @purpose	: A line that will render the 
			  the projectiles path.

 ------------------------------------------------- */

#pragma once

#include "GL_Program.h"
#include "GL_Matrix.h"

class Trajectory
{
private:

	GL_Program * m_pProgram;		// Shader
	GL_Matrix * m_pMatrix;			// Matrix

	vector<vec2> positions;			// Buffer Positions
	vec2 m_Start;					// Starting point
	
	GLuint m_Position;				// Position in array
	GLuint VAO;						// Vertex array object
	GLuint VBO;						// Vertex buffer object

public:

	// Constructor & Deconstructor
	Trajectory();
	~Trajectory();

	// Member Functions
	void PlotPoint(int, int, float);
	void ResetStart(float, float);
	void StartFrom(int, int, float);
	void Render();
	void Clear();

	GL_Matrix* getMatrix() { return m_pMatrix; }
};