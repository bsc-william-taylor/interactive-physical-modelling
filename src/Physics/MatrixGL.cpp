

#include "MatrixGL.h"

MatrixGL::MatrixGL()
{	
}

MatrixGL::~MatrixGL()
{ 
}

GLvoid MatrixGL::perspective(const float fov, const vec2 v, const vec2 d)
{
	auto aspectRatio = v.x / v.y;
	projectionMatrix = mat4(1.0f);
	projectionMatrix = glm::perspective(fov, aspectRatio, d.x, d.y);
}

GLvoid MatrixGL::loadIdenditity()
{
	modelMatrix = mat4(1.0f);
}

GLvoid MatrixGL::ortho(const vec2 w, const vec2 h, const vec2 d)
{
	projectionMatrix = mat4(1.0f);
	projectionMatrix = glm::ortho(w.x, w.y, h.x, h.y, d.x, d.y);
}

GLvoid MatrixGL::lookAt( const vec2 p )
{
	viewMatrix = mat4(1.0f);
	viewMatrix = glm::lookAt(vec3(p.x, p.y, 0.0f), vec3(p.x, p.y, -1.0f), vec3(0.0f, 1.0f, 0.0f) );
}

GLvoid MatrixGL::scale(const vec3 scale)
{
	modelMatrix = glm::scale(modelMatrix, scale);
}

GLvoid MatrixGL::rotateView(const float angle, const vec3 vec)
{
	viewMatrix = glm::rotate(viewMatrix, angle, vec);
}

GLvoid MatrixGL::ortho(const vec2 w, const vec2 h)
{
	projectionMatrix = mat4(1.0f);
	projectionMatrix = glm::ortho(w.x, w.y, h.x, h.y, -1.0f, 1.0f);
}

GLvoid MatrixGL::translate(const vec3 vector)
{
	modelMatrix = glm::translate(modelMatrix, vector);
}

GLvoid MatrixGL::translateView(const vec3 vector)
{
	viewMatrix = glm::translate(viewMatrix, vector);
}

GLvoid MatrixGL::rotate(const float angle, const vec3 vector)
{
	modelMatrix = glm::rotate(modelMatrix, angle, vector);
}

mat4 MatrixGL::getProjection()
{
	return projectionMatrix;
}

mat4 MatrixGL::getModel()
{
	return modelMatrix;
}

mat4 MatrixGL::getView()
{
	return viewMatrix;
}