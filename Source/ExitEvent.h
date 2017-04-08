
/* -------------------------------------------------
  
 @Filename  : ExitEvent.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Exit Event for when the user wishes
			  to exit the game.

 ------------------------------------------------- */

#pragma once

#include "Win32Header.h"
#include "IEvent.h"

class ExitEvent : public IEvent
{
public:

	std::string VMessage();			// Msg to be put into the log.
	void VOnTriggered(void *);			// Event handler.
};