
/* -------------------------------------------------
  
 @Filename  : IEvent.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A simple interface for all events
			  that need to be called
 ------------------------------------------------- */

#pragma once

#include <string>

class IEvent
{
public:

	virtual std::string VMessage() = 0;
	virtual void VOnTriggered(void *) = 0;
};