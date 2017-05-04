
#pragma once

#include "TextureGL.h"
#include "Main.h"

class Projectile
{
    TextureGL texture;
    ObjectGL object;

    vec2 startVelocity;
    vec2 startPoint;
    vec2 velocity;
    vec2 position;
    vec2 offset;
    vec3 size;
    float mass;

    bool dragForce;
    bool fired;
public:
    Projectile();
    ~Projectile();

    float getMass();

    void setup(vec2);
    void setMass(float);
    void setVelocity(vec2);
    void setPosition(vec2);
    void setOffset(vec2);
    void setSize(vec2);
    void reset(float angle);
    void toggleDragForce();
    void onUpdate();
    void fire();

    vec2 getPosition();
    vec2 getStartPos();
    vec2 getVelocity();

    TextureGL* getSprite();
    ObjectGL* getObject();

    bool hasFired();
};