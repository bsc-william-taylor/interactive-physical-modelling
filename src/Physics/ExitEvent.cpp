
#include "ExitEvent.h"

void ExitEvent::onTriggered(void* pData)
{
    PostQuitMessage(0);
}

std::string ExitEvent::getMessage()
{
    return "User Exits Demo";
}