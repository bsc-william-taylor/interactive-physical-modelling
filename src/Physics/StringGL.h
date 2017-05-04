
#pragma once

#include "TextureManagerGL.h"
#include "TextureGL.h"

class StringGL
{
	tinyxml2::XMLDocument* document;
    std::string fontname;
    std::string text;

	GLfloat colour[4];
	GLuint height;
	GLuint width;
	GLuint vbo;
	GLuint vao;

    SpriteGL* sprite;
    ObjectGL* object;
public:
	StringGL(std::string font = "", std::string tex = "");
	~StringGL();

    ObjectGL* getObject();

	GLvoid prepare();
    GLvoid prepareFont(std::string fontname, std::string texture);
	GLvoid setColour(GLfloat, GLfloat, GLfloat, GLfloat);
	GLvoid setParameters(ObjectGL *);
	GLvoid setString(std::string, int spacing = 0);

	std::string getString();

	GLuint getStringLength();
	GLuint getVertexArray();
	GLuint getTextureID();
	GLuint getHeight();
	GLuint getWidth();

    GLfloat* getColour();
};