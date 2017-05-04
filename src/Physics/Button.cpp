
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
    //SAFE_RELEASE(event);
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

    charTexture.setTexture(filename.c_str(), GL_CLAMP_TO_EDGE);
    charTexture.setParameters(&textureObject);
    charTexture.Prepare();

    textObject.setOrtho2D(vec4(0, 0, 1280, 720));
    textObject.setPosition(pos);
    textObject.setSize(vec2(25, 25));

    string.setParameters(&textObject);
    string.setString(text.c_str());
    string.Prepare();

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

void Button::onMouseState(int Key, int State, int x, int y)
{
    auto events = EventManager::get();

    if (x >= position.x && x <= position.x + size.x && y >= position.y && y <= position.y + size.y)
    {
        if (Key == MOUSE_1 && State == RELEASED && event != nullptr)
        {
            events->triggerEvent(event, false, this);
        }
    }
}

GL_Texture* Button::getTexture()
{
    return &charTexture;
}

GL_String* Button::getString()
{
    return &string;
}