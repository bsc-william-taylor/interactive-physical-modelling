
#include "GL_Texture_Manager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Main.h"

Demo::Demo() : framerate(60)
{
    SetConsoleTitle("Debug Console");
}

Demo::~Demo()
{
    RELEASE_MANAGER(GL_TextureManager::get());
    RELEASE_MANAGER(GL_Shader_Manager::get());
    RELEASE_MANAGER(SceneManager::get());
    RELEASE_MANAGER(EventManager::get());
}

void Demo::setupWindow()
{
    Window::SIZES size;

    size.w = 1280;
    size.h = 720;
    size.x = 0;
    size.y = 0;

    system.setWindowTraits("Physics Demo", size);
    system.setWindowType(Win32Window::WINDOWED);
    system.Initialise();
}

void Demo::setupStates()
{
    auto sceneManager = SceneManager::get();
    sceneManager->PushState(new MainMenu());
    sceneManager->PushState(new MainScene());
    sceneManager->StartFrom((int)SceneStates::MainMenu);
    sceneManager->EnableFactory();
}

void Demo::setFrameRate(unsigned int framerate)
{
    this->framerate = framerate;
}

void Demo::execute()
{
    timer.Start();

    setupWindow();
    setupStates();

    auto Events = EventManager::get();
    auto Scenes = SceneManager::get();

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Main Game Loop
    while (system.WindowRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        system.Update();

        Events->UpdateManager();
        Scenes->UpdateManager();

        system.SwapWindowBuffers();

        auto timeLeft = 0.0;

        while (timeLeft < (double)1.0e9 / framerate)
        {
            timer.Stop();
            timeLeft = timer.Difference(TimeType::NS);
        }

        timer.Start();
    }
}

#ifdef WINDOW_MAIN
#define MAIN WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPSTR str, INT show)
#else
#define MAIN main(int argc, const char * argv[])
#endif

int MAIN
{
    Demo demo;
    demo.execute();
    return 0;
}