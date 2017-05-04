
#pragma once

#include "HeaderGL.h"

struct SpriteGL
{
    GLuint uniqueID;
	GLuint height;
	GLuint width;
};

class TextureManagerGL
{
	static TextureManagerGL* manager;		
	std::map<std::string, SpriteGL*> textures;			
public:
	~TextureManagerGL();
    TextureManagerGL();

	static TextureManagerGL * get();	

	SpriteGL* createTexture(GLubyte *, GLuint, GLuint, GLenum);
	SpriteGL* createTexture(const std::string&, GLenum);
    SpriteGL* loadTexture(const std::string&, GLenum e);

	GLuint getTextureCount();
    GLvoid freeTextures();
};