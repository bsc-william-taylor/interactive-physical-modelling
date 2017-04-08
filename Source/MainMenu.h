
/* -------------------------------------------------
  
 @Filename  : MainMenu.h
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: The main menu scene obviously :P

 ------------------------------------------------- */

#pragma once

#include "MenuButtons.h"
#include "MenuImages.h"
#include "MenuLabels.h"
#include "Scene.h"

class MainMenu : public Scene
{ 
private:

	MenuButtons * m_pButtons;
	MenuLabels * m_pLabels;
	MenuImages * m_pImages;

public:

	// Constructor & Deconstructor
	MainMenu();
	~MainMenu();
	
	// Member Functions
	void MousePress(int, int, int, int);
	void VOnCommit(SceneFactory *);
	void KeyPress(int, int);
	void Update();
	void Render();
};