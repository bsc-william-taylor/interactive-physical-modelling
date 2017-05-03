
#include "SceneManager.h"
#include "PlayEvent.h"
#include "Scenes.h"

void PlayEvent::onTriggered(void* pData)
{
    SceneManager::get()->SwitchTo((int)SceneStates::MainScene);
}

std::string PlayEvent::getMessage()
{
    return "User Starts Demo";
}