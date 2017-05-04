
#include "SceneManager.h"
#include "UiEvent.h"
#include "MainScene.h"
#include "Main.h"

void UiEvent::onTriggered(void* data)
{
    auto current = SceneManager::get()->getCurrent();
    auto scene = dynamic_cast<MainScene*>(current);

    if (scene)
    {
        scene->onUiEvent(data);
    } 
}

std::string UiEvent::getMessage()
{
    return "Ui Event";  
}