


#pragma once

#include "TextureGL.h"
#include "Main.h"

class Target
{
    TextureGL texture;
    ObjectGL object;
    float mass;
    vec2 position;
    bool clicked;
public:
    Target();
    ~Target();

    void setMass(float);
    void setPosition(vec2);
    void setup(vec2);
    void onUpdate();
    void onMousePress(int, int, int, int);

    TextureGL* getSprite();
    ObjectGL* getObject();
    vec2 getPosition();
};