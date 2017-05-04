
#include "GL_Texture_Manager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "MainScene.h"
#include "MainMenu.h"
#include "Main.h"

Demo::Demo() : framerate(60)
{
    SetConsoleTitle("Debug Console");
}

Demo::~Demo()
{
    SAFE_RELEASE_SINGLETON(TextureManagerGL::get());
    SAFE_RELEASE_SINGLETON(ShaderManagerGL::get());
    SAFE_RELEASE_SINGLETON(SceneManager::get());
    SAFE_RELEASE_SINGLETON(EventManager::get());
}

void Demo::setupWindow()
{
    const auto center = (int)WindowLocation::Center;
    system.setWindowTraits("Physics Demo", { center, center, 1280, 720 });
    system.setWindowType(WindowType::Windowed);
    system.initialise();
}

void Demo::setupStates()
{
    auto sceneManager = SceneManager::get();
    sceneManager->pushState(new MainMenu());
    sceneManager->pushState(new MainScene());
    sceneManager->startFrom((int)SceneStates::MainMenu);
    sceneManager->enableFactory();
}

void Demo::setFrameRate(int framerate)
{
    this->framerate = framerate;
}

void Demo::execute()
{
    timer.start();
    setupWindow();
    setupStates();

    auto events = EventManager::get();
    auto scenes = SceneManager::get();

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    while (system.windowRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, 1280, 720);

        system.onUpdate();
        events->updateManager();
        scenes->updateManager();
        system.swapWindowBuffers();

        auto timeLeft = 0.0;

        while (timeLeft < (double)1.0e9 / framerate)
        {
            timer.stop();
            timeLeft = timer.difference(TimeType::Nanoseconds);
        }

        timer.start();
    }
}

int MAIN
{
    Demo demo;
    demo.execute();
    return 0;
}