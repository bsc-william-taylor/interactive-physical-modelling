
#pragma once

#include "TextureGL.h"
#include "Projectiles.h"
#include "Trajectory.h"

class Cannon
{
    vector<TextureGL *> sprites;

    Projectiles projectiles;
    ObjectGL staticObject;
    ObjectGL rotateObject;
    Material material;

    float angle;
public:
    Cannon();
    ~Cannon();

    vector<TextureGL *>& getTextures();

    void onKeyPress(int, int);
    void initialise();
    void onUpdate();
    void fire();

    ObjectGL* getStaticObject();
    ObjectGL* getRotateObject();

    Projectiles* getProjectiles();
    Trajectory* getTrajectory();
    Projectile* getProjectile();
    Material getBallMaterial();

    float getAngle();
};