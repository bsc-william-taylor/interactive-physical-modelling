
#include "SceneManager.h"
#include "PlayEvent.h"
#include "Main.h"

void PlayEvent::onTriggered(void* pData)
{
    SceneManager::get()->SwitchTo((int)SceneStates::MainScene);
}

std::string PlayEvent::getMessage()
{
    return "User Starts Demo";
}