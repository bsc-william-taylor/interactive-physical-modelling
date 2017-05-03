
#include "BackEvent.h"

void BackEvent::onTriggered(void* data)
{
    SceneManager::get()->PreviousScene();
}

std::string BackEvent::getMessage()
{
    return "User Returns To Menu";
}