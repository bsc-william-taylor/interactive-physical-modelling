
/* -------------------------------------------------
  
 @Filename  : SceneManager.cpp
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: Simple include file that includes
              all app scenes as well as constants
			  to move to them with the scenemanager.

 ------------------------------------------------- */

#pragma once

#include "MainMenu.h"
#include "MainScene.h"

// Should be used with SwitchState(unsigned int);
enum States 
{
	MAIN_MENU,
	MAIN_SCENE
};