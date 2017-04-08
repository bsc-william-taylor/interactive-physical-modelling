
/* -------------------------------------------------
  
 @Filename  : BackEvent.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Back Event for when the user wishes
			  to go back to main menu.

 ------------------------------------------------- */

#pragma once

#include "SceneManager.h"
#include "IEvent.h"

class BackEvent : public IEvent
{
public:
	std::string VMessage();		// Msg to be put into the log.
	void VOnTriggered(void *);		// Event handler
};