
#include "EventManager.h"
#include "Win32Codes.h"
#include "ExitEvent.h"
#include "MainMenu.h"

MainMenu::MainMenu() :
    title("data/largeText.xml", "data/LargeText.png")
{
    for (int i = 0; i < 3; i++)
    {
        m_Banners[i].prepareFont("data/LargeText.xml", "data/LargeText.png");
    }

    setupLabels();
    setupButtons();
    setupImages();
}

MainMenu::~MainMenu()
{
}

void MainMenu::setupLabels()
{
    std::string names[] = { "B00233705", "B00235610", "B00243868" };
    titleObject.setOrtho2D(vec4(0, 0, 800, 540));
    titleObject.setScale(vec3(0.5, 0.5, 0.5));
    titleObject.setPosition(vec2(100, 750));
    titleObject.setSize(vec2(53, 53));

    title.setParameters(&titleObject);
    title.setString("Physics Demo Coursework", 5);
    title.prepare();

    for (int i = 0, position = 300; i < 3; i++)
    {
        m_Objects[i].setOrtho2D(vec4(0, 0, 800, 540));
        m_Objects[i].setPosition(vec2(150, position));
        m_Objects[i].setScale(vec3(0.35, 0.35, 0.35));
        m_Objects[i].setSize(vec2(35, 35));

        m_Banners[i].setParameters(&m_Objects[i]);
        m_Banners[i].setString(names[i], 5);
        m_Banners[i].prepare();

        position += 150;
    }
}

void MainMenu::setupButtons()
{
    playButton.setPosition("Play", vec2(800, 200), vec2(200, 60));
    playButton.onPress(new PlayEvent());
}

void MainMenu::setupImages()
{
    backgroundObject.setOrtho2D(vec4(0, 0, 1280, 720));
    backgroundObject.setPosition(vec2(0, 0));
    backgroundObject.setSize(vec2(3000, 1383));

    backgroundTexture.setTexture("data/img/background.png", GL_CLAMP_TO_EDGE);
    backgroundTexture.setParameters(&backgroundObject);
    backgroundTexture.prepare();
}

void MainMenu::onUpdate()
{
}

void MainMenu::onRender()
{
    renderer.renderTexture(&backgroundTexture);

    for (int i = 0; i < 3; i++)
    {
        renderer.renderString(&m_Banners[i]);
    }

    renderer.renderString(&title);
    renderer.renderTexture(playButton.getTexture());
    renderer.renderString(playButton.getString());
}

void MainMenu::onKeyPress(int Key, int State)
{
    auto events = EventManager::get();

    if (KEY_DOWN(ESCAPE, Key, State))
    {
        events->triggerEvent(500, new ExitEvent(), this);
    }
}

void MainMenu::onMousePress(int key, int state, int x, int y)
{
    playButton.onMouseState(key, state, x, y);
}

void MainMenu::onCommit(SceneFactory * factory)
{
    factory->PushAsset("MenuBackground", &backgroundTexture);
}
