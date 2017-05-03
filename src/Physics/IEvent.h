
#pragma once

#include <string>

class IEvent
{
public:
    virtual ~IEvent() = default;
	virtual std::string getMessage() = 0;
	virtual void onTriggered(void *) = 0;
};