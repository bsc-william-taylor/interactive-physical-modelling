
#pragma once

#include "IEvent.h"

class PlayEvent : public IEvent
{
public:
    std::string getMessage();			
    void onTriggered(void *);			
};