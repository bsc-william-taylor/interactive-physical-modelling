
/* -------------------------------------------------
  
 @Filename  : BackEvent.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation.

 ------------------------------------------------- */

#include "BackEvent.h"

// Constructor not really needed for something so basic.
// Handler Function
void BackEvent::VOnTriggered(void * pData)
{
	SceneManager::get()->PreviousScene();
}

// Msg to be posted to the event log
std::string BackEvent::VMessage() 
{
	return("User Returns To Menu");
}