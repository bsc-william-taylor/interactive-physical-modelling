
#pragma once

#include "SceneManager.h"
#include "IEvent.h"

class BackEvent : public IEvent
{
public:
    std::string getMessage();
    void onTriggered(void *);
};