
#include "Win32Codes.h"
#include "Cannon.h"
#include "Main.h"

Cannon::Cannon() :
    material(Material::Iron),
    angle(0)
{
    for (int i = 0; i < 3; i++)
    { 
        sprites.push_back(new TextureGL());
    }
}

Cannon::~Cannon()
{
    for (auto sprite : sprites)
    { 
        delete sprite;
    }
}

void Cannon::initialise()
{
    rotateObject.setOrtho2D(vec4(0, 0, 1280, 720));
    rotateObject.setPosition(vec2(0, 0));
    rotateObject.setSize(vec2(235, 96));

    staticObject.setOrtho2D(vec4(0, 0, 1280, 720));
    staticObject.setPosition(vec2(0, 0));
    staticObject.setSize(vec2(235, 96));

    std::string filenames[3] = {
        "data/img/c3.png",
        "data/img/cannon96.png",
        "data/img/c1.png"
    };

    for (int i = 0; i < 3; i++)
    {
        sprites[i]->setTexture(filenames[i], GL_CLAMP_TO_EDGE);
        sprites[i]->setParameters(i == 1 ? &rotateObject : &staticObject);
        sprites[i]->prepare();
    }

    projectiles.setMaxProjectiles(1);

    float cannonLengthX = 90.0f * cosf(glm::radians(angle));
    float cannonLengthY = 90.0f * sinf(glm::radians(angle));
    float xComponent(FULCRUM_X - 10 + cannonLengthX);		
    float yComponent(FULCRUM_Y - 10 + cannonLengthY);		

    projectiles.initialise(angle, vec2(xComponent, yComponent), vec2(xComponent, yComponent));
}

Trajectory * Cannon::getTrajectory()
{
    return projectiles.getTrajectory();
}

void Cannon::fire()
{
    projectiles.fireProjectile(angle);
}

void Cannon::onKeyPress(int key, int state)
{
    if (key == ARROW_DOWN && angle > 0)
    {
        angle--;
    }

    if (key == ARROW_UP && angle < 90)
    {
        angle++;
    }


    switch (key)
    {
    case FOUR:
        projectiles.setMaterial(Material::Stone);
        material = Material::Stone; 
        break;
    case THREE: 
        projectiles.setMaterial(Material::Copper); 
        material = Material::Copper; 
        break;
    case TWO:
        projectiles.setMaterial(Material::Aluminium); 
        material = Material::Aluminium; 
        break;
    case ONE: 
        projectiles.setMaterial(Material::Iron); 
        material = Material::Iron; 
        break;

    default: 
        break;
    };
}

Projectile* Cannon::getProjectile()
{
    return projectiles.getTextures().at(0);
}

void Cannon::onUpdate()
{
    staticObject.setIdentity();
    rotateObject.setIdentity();

    rotateObject.setTranslate(vec2(FULCRUM_X, FULCRUM_Y));
    rotateObject.setRotation(glm::radians((float)angle), vec3(0.0, 0.0, 1.0));
    rotateObject.setTranslate(-vec2(FULCRUM_X, FULCRUM_Y));

    projectiles.onUpdate();
}

std::vector<TextureGL *>& Cannon::getTextures()
{
    return sprites;
}

Projectiles* Cannon::getProjectiles()
{
    return &projectiles;
}

ObjectGL * Cannon::getStaticObject() 
{ 
    return &staticObject; 
}

ObjectGL * Cannon::getRotateObject() 
{ 
    return &rotateObject; 
}

Material Cannon::getBallMaterial() 
{ 
    return material; 
}

float Cannon::getAngle()
{ 
    return angle; 
}