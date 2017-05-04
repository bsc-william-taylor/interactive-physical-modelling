
/* -------------------------------------------------
  
 @Filename  : Trajectory.h
 @author	: William Taylor
 @date		: 27/02/2014
 @purpose	: A line that will render the 
			  the projectiles path.

 ------------------------------------------------- */

#pragma once

#include "ProgramGL.h"
#include "MatrixGL.h"

class Trajectory
{
private:

	ProgramGL * m_pProgram;		// Shader
	MatrixGL * m_pMatrix;			// Matrix

	vector<vec2> positions;			// Buffer Positions
	vec2 m_Start;					// Starting point
	
	GLuint position;				// Position in array
	GLuint VAO;						// Vertex array object
	GLuint VBO;						// Vertex buffer object

public:

	// Constructor & Deconstructor
	Trajectory();
	~Trajectory();

	// Member Functions
	void PlotPoint(int, int, float);
	void ResetStart(float, float);
	void startFrom(int, int, float);
	void onRender();
	void Clear();

	MatrixGL* getMatrix() { return m_pMatrix; }
};