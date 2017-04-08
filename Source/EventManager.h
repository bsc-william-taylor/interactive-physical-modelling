
/* -------------------------------------------------
  
 @Filename  : EventManager.h
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: A singleton for managing all events
			 that the game will generate.

 ------------------------------------------------- */

#pragma once

#include "EventLogger.h"
#include "Win32Timer.h"
#include "IEvent.h"

class EventManager
{
private:

	// Custom data type for the timed events
	struct TimedEvent
	{
		Win32Timer * m_pTimer;
		IEvent * m_pEvent;
		unsigned int ms;
		void * pData;
	};

private:

	static EventManager * m_pEventManager;		// Static instance
	vector<TimedEvent *> m_vTimedEvents;		// All timed events
	EventLogger * m_pEventLogger;				// Event logger

public:

	// Constructor & Deconstructor
	EventManager();
	~EventManager();

	// Member Functions
	void TriggerEvent(unsigned int, IEvent *, void *);
	void TriggerEvent(IEvent *, bool, void *);
	void UpdateManager();

	// Get & Set Functions
	static EventManager * get();
};