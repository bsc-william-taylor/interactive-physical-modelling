
#pragma once

#include "IEvent.h"

class UiEvent : public IEvent
{
public:
    std::string getMessage();
    void onTriggered(void *);
};