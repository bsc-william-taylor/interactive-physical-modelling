
#include "BackEvent.h"

void BackEvent::onTriggered(void* data)
{
    SceneManager::get()->previousScene();
}

std::string BackEvent::getMessage()
{
    return "User Returns To Menu";
}