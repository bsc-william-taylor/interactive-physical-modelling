
/* -------------------------------------------------
  
 @Filename  : Trajectory.h
 @author	: William Taylor
 @date		: 27/02/2014
 @purpose	: A line that will render the 
			  the projectiles path.

 ------------------------------------------------- */

#include "ShaderManagerGL.h"
#include "Trajectory.h"

// Constructor & Deconstructor
Trajectory::Trajectory()
	: m_pMatrix(new MatrixGL()),
	  position(0)
{
	// Set up objects needed
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// set defailt line length & other settings
	glEnable(GL_LINE_SMOOTH); 
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glLineWidth(2.0f);
}

Trajectory::~Trajectory()
{
	// Delete objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Trajectory::PlotPoint(int x, int y, float r)
{
	// Plot new point into the array
	if(position + 1 < positions.size())
	{
		++position;

		positions[position].x = (GLfloat)(x + r);
		positions[position].y = (GLfloat)(y + r);

		// Bind new data into the buffer
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * positions.size(), &positions[0], GL_DYNAMIC_DRAW); 
	
		// re-enable the pointer
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
}

void Trajectory::startFrom(int x, int y, float r)
{
	// Shader files
	const GLchar * vs = "data/shaders/Trajectory.vert";
	const GLchar * fs = "data/shaders/Trajectory.frag";

	// Load program & Set projection
	m_pProgram = ShaderManagerGL::get()->getShader(vs, fs);
	m_pMatrix->ortho(vec2(0, 1280), vec2(0, 720));
	m_Start = vec2(x + r, y + r);

	// Initialise Array
	for(GLint i = 0; i < 800; i++)
	{
		positions.push_back(vec2(x + r, y + r));
	}
}

void Trajectory::ResetStart(float x, float y)
{
	m_Start = vec2(x, y);
	for(GLint i = 0; i < 800; i++)
	{
		positions[i] = vec2(x + 5.0f, y + 5.0f);
	} 
}

void Trajectory::onRender()
{
	// Use the Shader
	m_pProgram->use();
	m_pProgram->setMatrix("Projection", m_pMatrix->getProjection());
	m_pProgram->setMatrix("Model", m_pMatrix->getModel());
	m_pProgram->setMatrix("View", m_pMatrix->getView());
	
	glUniform2fv(m_pProgram->getUniform("Start"), 1, glm::value_ptr(m_Start));

	// Bind the Vertex array object & Draw
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, position);
	glBindVertexArray(0);

	// Release Shader
	m_pProgram->release();
}

void Trajectory::Clear()
{
	// Reset positions & Array location
	position = 0;
	for(GLint i = 0; i < 800; i++)
	{
		positions[i] = vec2(0, 0);
	} 
}