
#pragma once

#include "RendererGL.h"
#include "Projectile.h"
#include "Trajectory.h"

enum class Material
{
    Iron = 1,
    Aluminium,
    Copper,
    Stone
};

class Projectiles
{
    vector<Projectile*> projectiles;
    vector<GLuint> textureIDs;
    Trajectory * trajectory;
    unsigned int count;
    unsigned int max;
    vec3 scale;
public:
    Projectiles();
    ~Projectiles();

    void setMaxProjectiles(unsigned int);
    void setMaterial(Material);
    void initialise(float angle, vec2, vec2);
    void fireProjectile(float angle);
    void onUpdate();

    vector<Projectile*>& getTextures();
    Trajectory* getTrajectory();
};