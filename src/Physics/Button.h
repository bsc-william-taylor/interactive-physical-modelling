
#pragma once

#include "EventManager.h"
#include "TextureGL.h"
#include "StringGL.h"
#include "IEvent.h"

class Button
{
    std::string filename;
    vec2 position, size;
    IEvent* event;

    TextureGL texture;
    ObjectGL textureObject;
    ObjectGL textObject;
    StringGL string;
public:
    Button();
    ~Button();

    void setPosition(const std::string&, vec2, vec2);
    void setTexture(const std::string&);
    void onMouseState(int, int, int, int);
    void onPress(IEvent *);

    TextureGL* getTexture();
    StringGL* getString();
};