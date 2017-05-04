
#pragma once

#include "TextureGL.h"
#include "StringGL.h"

class RendererGL
{
    vector<TextureGL *> textures;
    vector<StringGL *> labels;
public:
    RendererGL();
    ~RendererGL();

    GLvoid renderTexture(TextureGL*);
    GLvoid renderString(StringGL*);
    GLvoid pushTexture(TextureGL*);
    GLvoid pushText(StringGL*);
    GLvoid prepare();
    GLvoid onRender();
};