
#pragma once

#include "TextureManagerGL.h"
#include "ShaderManagerGL.h"
#include "ObjectGL.h"

class TextureGL
{
    SpriteGL* texture;
    ObjectGL* object;

    GLenum setting;
    GLuint vao;
    GLuint vbo;

    std::string path;
public:
    TextureGL();
    ~TextureGL();

    ObjectGL* getObject();

    GLvoid prepare();
    GLvoid setParameters(ObjectGL*);
    GLvoid setTexture(std::string, GLenum);
    GLvoid setID(GLuint);

    GLuint getTextureID();
    GLuint getVAO();

    const std::string& getPath();
};
