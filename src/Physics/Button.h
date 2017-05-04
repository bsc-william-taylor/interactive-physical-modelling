
#pragma once

#include "EventManager.h"
#include "GL_Texture.h"
#include "GL_String.h"
#include "IEvent.h"

class Button
{
    std::string filename;
    vec2 position, size;
    IEvent* event;

    GL_Texture charTexture;
    GL_Object textureObject;
    GL_Object textObject;
    GL_String string;
public:
    Button();
    ~Button();

    void setPosition(const std::string&, vec2, vec2);
    void setTexture(const std::string&);
    void onMouseState(int, int, int, int);
    void onPress(IEvent *);

    GL_Texture* getTexture();
    GL_String* getString();
};