/* -------------------------------------------------
  
 @Filename  : EventManager.h
 @author	: William Taylor
 @date		: 19/02/2014

 @purpose	: A singleton for managing all events
			 that the game will generate.

 ------------------------------------------------- */

#include "EventManager.h"

EventManager * EventManager::m_pEventManager = 0;

// Constructor & Deconstructor
EventManager::EventManager() 
	: m_pEventLogger(new EventLogger("log.txt"))
{
	m_pEventLogger->Initialise();
}

EventManager::~EventManager()
{
	// Release Logs
	SAFE_RELEASE(m_pEventLogger);
}

// Member Functions
void EventManager::TriggerEvent(IEvent * event, bool destroy, void * data)
{
	// Make sure event has been created
	if(event != NULL) 
	{
		m_pEventLogger->WriteEventLog(event);
		event->VOnTriggered(data);

		// If asked the event will be deleted.
		if(destroy) 
		{
			m_pEventLogger->EventReleased();
			SAFE_RELEASE(event);
		}
	}
}

void EventManager::TriggerEvent(unsigned int ms, IEvent * event, void * data)
{
	// Create a new event
	TimedEvent * Event = new TimedEvent();
	
	// initialise timer
	Event->m_pTimer = new Win32Timer();
	Event->m_pTimer->Start();
	Event->m_pEvent = event;
	Event->pData = data;
	Event->ms = ms;

	// push event to the timed events vector
	m_vTimedEvents.push_back(Event);
}

void EventManager::UpdateManager()
{
	// Go through the vector and check all timed events
	for(unsigned int i = 0; i < m_vTimedEvents.size(); i++)
	{
		auto Event = m_vTimedEvents[i];
		
		// if the time has passed trigger the event.
		Event->m_pTimer->Stop();
		if(Event->m_pTimer->Difference(TimeType::MS) >= Event->ms)
		{
			// Activiate event & Delete event & timer
			Event->m_pEvent->VOnTriggered(Event->pData);
			delete Event->m_pTimer;
			delete Event->m_pEvent;

			// resize array to remove the null element. 
			auto size = m_vTimedEvents.size() - 1;
			m_vTimedEvents.resize(size);
		}
	}
}

// Get & Set Functions
EventManager * EventManager::get()
{
	if(!m_pEventManager) 
	{
		m_pEventManager = new EventManager();
	}

	return m_pEventManager;
}