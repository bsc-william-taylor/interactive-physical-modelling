
/* -------------------------------------------------
  
 @Filename  : EventLogger.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A Event logger that will write
			  events to a file which place is
			  set by the constructor

 ------------------------------------------------- */

#pragma once

#include "IEvent.h"

class EventLogger
{
private:

	std::string m_Filename;			// The logs filename
	unsigned int m_Msgs;			// The number of msgs written
	FILE * m_pFile;					// Ptr to the file itself

public:

	// Constructor & Deconstructor
	EventLogger(std::string);	
	~EventLogger();

	// Member Functions
	void WriteEventLog(IEvent *);
	void EventReleased();
	void Initialise();
	void EventKept();

	// Get & Set Functions
	unsigned int numMessagesWritten();
};