
#include "TextureManagerGL.h"
#include "Projectiles.h"
#include "Main.h"

Projectiles::Projectiles()
    : count(0), max(10)
{
    auto manager = TextureManagerGL::get();
    trajectory = new Trajectory();

    textureIDs.push_back(manager->createTexture("data/img/iron.png", GL_CLAMP_TO_EDGE)->uniqueID);
    textureIDs.push_back(manager->createTexture("data/img/aluminium.png", GL_CLAMP_TO_EDGE)->uniqueID);
    textureIDs.push_back(manager->createTexture("data/img/copper.png", GL_CLAMP_TO_EDGE)->uniqueID);
    textureIDs.push_back(manager->createTexture("data/img/steel.png", GL_CLAMP_TO_EDGE)->uniqueID);
}

Projectiles::~Projectiles()
{
    for (auto projectile : projectiles)
    {
        delete projectile;
    }

    delete trajectory;
}

void Projectiles::initialise(float angle, vec2 vec, vec2 startPosition)
{
    auto xVariation = cosf(glm::radians(angle));
    auto yVariation = sinf(glm::radians(angle));

    trajectory->startFrom(vec.x, vec.y, 5.0f);

    for (auto i = 0; i < max; i++)
    {
        auto p = new Projectile();
        p->setOffset(vec2(xVariation, yVariation));
        p->setMass(10.0);
        p->setup(startPosition);
        projectiles.push_back(p);
    }
}

Trajectory* Projectiles::getTrajectory()
{
    return trajectory;
}

void Projectiles::fireProjectile(float angle)
{
    if (count < max)
    {
        projectiles[count]->reset(angle);
        projectiles[count]->fire();
    }
    else
    {
        projectiles[0]->reset(angle);
        count = 0;
    }

    auto point = projectiles[count]->getPosition() + projectiles[count]->getVelocity();
    trajectory->clear();
    trajectory->resetStart(point.x, point.y);
    count++;
}

void Projectiles::setMaterial(Material material)
{
    auto radius = 5.0f * CM;
    auto diametre = 2.0f * radius;
    auto volume = (4.0f / 3.0f) * pi<float>() * radius * radius * radius;
    auto density = DENSITY[(int)material - 1];
    auto mass = density * volume;

    projectiles[0]->getSprite()->setID(textureIDs[(int)material - 1]);
    projectiles[0]->setSize(vec2(diametre, diametre));
    projectiles[0]->setMass(mass);
}

void Projectiles::onUpdate()
{
    for (auto& projectile : projectiles)
    {
        projectile->onUpdate();
    }
}

vector<Projectile *>& Projectiles::getTextures()
{
    return projectiles;
}

void Projectiles::setMaxProjectiles(unsigned int newMax)
{
    this->max = newMax;
}