
#include "BackEvent.h"

void BackEvent::onTriggered(void* pData)
{
    SceneManager::get()->PreviousScene();
}

std::string BackEvent::getMessage()
{
    return "User Returns To Menu";
}