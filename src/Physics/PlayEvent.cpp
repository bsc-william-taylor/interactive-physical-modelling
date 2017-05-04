
#include "SceneManager.h"
#include "PlayEvent.h"
#include "Main.h"

void PlayEvent::onTriggered(void* data)
{
    SceneManager::get()->switchTo((int)SceneStates::MainScene);
}

std::string PlayEvent::getMessage()
{
    return "User Starts Demo";
}