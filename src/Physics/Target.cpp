
#include "Target.h"
#include "Win32Codes.h"

Target::Target()
{
    mass = 20.0f;
    clicked = false;
}

Target::~Target()
{
}

void Target::onUpdate()
{
    if (clicked)
    {
        return;
    }

    if (position.y - 10 < -TARGETHEIGHT / 2)
    {
        return;
    }

    if (mass)
    {
        vec2 Acceleration = GRAVITY * mass;

        position += Acceleration;

        object.setTranslate(Acceleration);
    }
}

void Target::setup(vec2 position)
{
    object.setOrtho2D(vec4(0, 0, 1280, 720));
    object.setPosition(position);
    object.setSize(vec2(TARGETWIDTH, TARGETHEIGHT));

    texture.setTexture("data/img/target.png", GL_CLAMP_TO_EDGE);
    texture.setParameters(&object);
    texture.prepare();

    this->position = position;
}

void Target::onMousePress(int button, int state, int x, int y)
{
    if (button == MOUSE_1 && state == HOLDING)
    {
        clicked = true;

        if (x >= position.x  && x <= (position.x + TARGETWIDTH))
        {
            if (y >= position.y && y <= (position.y + TARGETHEIGHT))
            {
                float y1 = (y - (position.y + TARGETHEIGHT / 2));
                float x1 = (x - (position.x + TARGETWIDTH / 2));

                object.setTranslate(vec2(x1, y1));

                position.x += x1;
                position.y += y1;
            }
        }
    }
    else
    {
        clicked = false;
    }
}

void Target::setMass(float mass)
{
    mass = mass;
}

void Target::setPosition(vec2 pos)
{
    position = pos;
}

TextureGL * Target::getSprite()
{
    return &texture;
}

vec2 Target::getPosition()
{
    return position;
}

ObjectGL* Target::getObject()
{
    return &object;
}