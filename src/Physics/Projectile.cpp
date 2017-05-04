

#include "Projectile.h"

Projectile::Projectile() :
    mass(1.0),
    fired(false),
    dragForce(true),
    size(vec3(1.0, 1.0, 1.0)),
    offset(vec2(0.0))
{
}

Projectile::~Projectile()
{
}

void Projectile::onUpdate()
{
    if (position.y <= TARGETHEIGHT / 4)
    {
        return;
    }

    object.setIdentity();

    if (fired)
    {
        vec2 prevTranslate = object.getTranslate();
        vec2 force;

        if (dragForce)
        {
            auto dim = object.getDimensions();
            auto radius = (dim.w - dim.y) / 2.0f;
            auto area = pi<float>() * radius * radius;

            force.x = -0.5f * (DENSITY_AIR)* DRAG_COEFICIENT * velocity.x * velocity.x * area;
        }

        velocity += force + GRAVITY;
        position += velocity;

        object.setTranslate(prevTranslate + velocity);
    }
}

void Projectile::toggleDragForce()
{
    dragForce = !dragForce;
}

void Projectile::setSize(vec2 vec)
{
    object.setSize(vec);
    size = vec3(vec.x, vec.y, 1.0f);
}

void Projectile::fire()
{
    fired = true;
}

float Projectile::getMass()
{
    return mass;
}

void Projectile::reset(float angle)
{
    object.setIdentity();
    object.setTranslate(vec2(0, 0));

    auto cannonLengthX = 90 * cosf(glm::radians(angle));
    auto cannonLengthY = 90 * sinf(glm::radians(angle));
    auto xComponent = FULCRUM_X - 10 + cannonLengthX;
    auto yComponent = FULCRUM_Y - 10 + cannonLengthY;

    position = vec2(xComponent, yComponent);
    velocity = vec2(0);

    vec2 startingAcceleration;
    startingAcceleration.x = FORCE * cosf(glm::radians(angle)) / mass;
    startingAcceleration.y = FORCE * sinf(glm::radians(angle)) / mass;
    velocity += startingAcceleration;

    setup(position);
}

void Projectile::setup(vec2 position)
{
    object.setOrtho2D(vec4(0, 0, 1280, 720));
    object.setPosition(position);
    object.setSize(vec2(size));

    texture.setTexture("data/img/iron.png", GL_CLAMP_TO_EDGE);
    texture.setParameters(&object);
    texture.prepare();

    this->position = position;
    startPoint = position;
}

void Projectile::setOffset(vec2 vec)
{
    offset = vec;
}

void Projectile::setMass(float mass)
{
    this->mass = mass;
}

void Projectile::setVelocity(vec2 vec)
{
    startVelocity = vec;
    velocity = vec;
}

void Projectile::setPosition(vec2 pos)
{
    position.x = pos.x;
    position.y = pos.y;
}

TextureGL * Projectile::getSprite()
{
    return &texture;
}

bool Projectile::hasFired()
{
    return fired;
}

vec2 Projectile::getPosition()
{
    return position;
}

vec2 Projectile::getStartPos()
{
    return startPoint;
}

vec2 Projectile::getVelocity()
{
    return velocity;
}

ObjectGL* Projectile::getObject()
{
    return &object;
}