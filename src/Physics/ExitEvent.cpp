
#include "ExitEvent.h"

void ExitEvent::onTriggered(void* data)
{
    PostQuitMessage(0);
}

std::string ExitEvent::getMessage()
{
    return "User Exits Demo";
}