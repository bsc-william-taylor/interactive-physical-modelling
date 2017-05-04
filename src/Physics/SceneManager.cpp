
#include "SceneManager.h"

SceneManager * SceneManager::manager = nullptr;

SceneManager::SceneManager()
    : factory(new SceneFactory()),
    currentScene(0)
{
}

SceneManager::~SceneManager()
{
    for (auto& scene : scenes)
    {
        delete scene;
    }

    manager = nullptr;
}

void SceneManager::startFrom(unsigned int startingPoint)
{
    currentScene = startingPoint;
}

void SceneManager::enableFactory()
{
    for (unsigned int i = 0; i < scenes.size(); i++)
    {
        scenes[i]->onCommit(factory);
    }

    for (unsigned int i = 0; i < scenes.size(); i++)
    {
        scenes[i]->onRequest(factory);
    }
}

void SceneManager::previousScene()
{
    currentScene--;
}

void SceneManager::nextScene()
{
    currentScene++;
}

void SceneManager::pushState(Scene * state)
{
    if (state != nullptr)
    {
        scenes.push_back(state);
    }
}

void SceneManager::updateManager()
{
    scenes[currentScene]->onUpdate();
    scenes[currentScene]->onRender();
}

void SceneManager::switchTo(unsigned int newPlace)
{
    scenes[currentScene]->onEnter();
    currentScene = newPlace;
    scenes[currentScene]->onExit();
}

Scene * SceneManager::getCurrent()
{
    if (scenes.empty())
    {
        return nullptr;
    }

    return scenes[currentScene];
}

SceneManager * SceneManager::get()
{
    if (manager == nullptr)
    {
        manager = new SceneManager();
    }

    return manager;
}