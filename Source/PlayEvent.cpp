
/* -------------------------------------------------
  
 @Filename  : PlayEvent.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation.

 ------------------------------------------------- */

#include "SceneManager.h"
#include "PlayEvent.h"
#include "Scenes.h"

// Constructor not really needed for something so basic.
// Handler Function
void PlayEvent::VOnTriggered(void *)
{
	SceneManager::get()->SwitchTo(MAIN_SCENE);
}

// Message to be printed to the logger
std::string PlayEvent::VMessage() 
{
	return "User Starts Demo";
}