
#include "Button.h"
#include "Win32Codes.h"

Button::Button() :
    filename("data/img/button.png"),
    string("data/text.xml", "data/tinyText.png"),
    event(nullptr)
{
}

Button::~Button()
{
    SAFE_RELEASE(event);
}

void Button::onPress(IEvent* event)
{
    this->event = event;
}

void Button::setPosition(const std::string& text, vec2 pos, vec2 sz)
{
    textureObject.setOrtho2D(vec4(0, 0, 1280, 720));
    textureObject.setPosition(pos);
    textureObject.setSize(sz);

    texture.setTexture(filename.c_str(), GL_CLAMP_TO_EDGE);
    texture.setParameters(&textureObject);
    texture.prepare();

    textObject.setOrtho2D(vec4(0, 0, 1280, 720));
    textObject.setPosition(pos);
    textObject.setSize(vec2(25, 25));

    string.setParameters(&textObject);
    string.setString(text.c_str(), 3);
    string.prepare();

    const auto height = (int)sz.y - string.getHeight();
    const auto width = (int)sz.x - string.getWidth();

    textObject.setTranslate(vec2(width / 2, height / 2));
    position = pos;
    size = sz;
}

void Button::setTexture(const std::string& file)
{
    filename = file;
}

void Button::onMouseState(int key, int state, int x, int y)
{
    auto events = EventManager::get();

    if (x >= position.x && x <= position.x + size.x && y >= position.y && y <= position.y + size.y)
    {
        if (key == MOUSE_1 && state == RELEASED && event != nullptr)
        {
            events->triggerEvent(event, false, this);
        }
    }
}

TextureGL* Button::getTexture()
{
    return &texture;
}

StringGL* Button::getString()
{
    return &string;
}