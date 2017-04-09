
/* -------------------------------------------------
  
 @Filename  : ExitEvent.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation.

 ------------------------------------------------- */

#include "ExitEvent.h"

// Constructor not really needed for something so basic.
// Handler Function
void ExitEvent::VOnTriggered(void *)
{
	PostQuitMessage(0);
}

// Msg to be posted to the event log
std::string ExitEvent::VMessage() 
{
	return("User Exits Demo");
}