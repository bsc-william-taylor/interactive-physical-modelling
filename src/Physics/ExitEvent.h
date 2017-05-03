
#pragma once

#include "Win32Header.h"
#include "IEvent.h"

class ExitEvent : public IEvent
{
public:
    std::string getMessage();
    void onTriggered(void *);
};