
/* -------------------------------------------------
  
 @Filename  : Demo.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Main Demo class acts as a centre 
			  point for the entire application

 ------------------------------------------------- */

#pragma once

#include "SceneManager.h"
#include "Win32System.h"
#include "Win32Timer.h"

class Demo
{
private:

	unsigned int m_Framerate;				// The framerate for the demo
	Win32System * m_pSystem;				// Win32 Application Layer
	Win32Timer * m_pTimer;					// A timer to control display rate

public:

	// Constructor & Deconstructor
	Demo();
	~Demo();

	// Member Functions
	void Execute();

	// Set & Get Functions
	void setFrameRate(unsigned int);

private:

	// Private set up functions to make code cleaner
	void SetupStates();
	void SetupWindow();
};

// END