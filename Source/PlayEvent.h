
/* -------------------------------------------------
  
 @Filename  : PlayEvent.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation.

 ------------------------------------------------- */

#pragma once

#include "IEvent.h"

class PlayEvent : public IEvent
{
public:
	std::string VMessage();			// Msg to be put into the log.
	void VOnTriggered(void *);			// Event handler.
};