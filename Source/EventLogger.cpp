
/* -------------------------------------------------
  
 @Filename  : EventLogger.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "EventLogger.h"
#include <assert.h>

// Constructor & Deconstructor
EventLogger::EventLogger(std::string filename)
	: m_Filename(filename),
	  m_Msgs(NULL)
{
}

EventLogger::~EventLogger()
{
	fclose(m_pFile);
}

// Member Functions
void EventLogger::Initialise()
{
	// Exception handling is used just to be safe.
	try {
		// Write a title to the file.
		std::string Header = "\n - Event Logger - \n\n";

		fopen_s(&m_pFile, m_Filename.c_str(), "w+");
		fseek(m_pFile, 0, SEEK_SET);
		fwrite(Header.c_str(), 1, Header.size(), m_pFile);

		++m_Msgs;
	} 
	catch (...)
	{
		// Close file to prevent data loss
		fclose(m_pFile);
		assert("Couldnt Setup Event Logger !!!");
	}
}

void EventLogger::WriteEventLog(IEvent * event)
{
	// Exception handling is used just to be safe.
	try 
	{
		auto msg = event->VMessage();
		fwrite(msg.c_str(), 1, msg.size(), m_pFile);
	} 
	catch (...) 
	{
		fclose(m_pFile);
		assert("Couldnt Write to logger");
	}
}

void EventLogger::EventReleased()
{
	// Exception handling is used just to be safe.
	try 
	{
		std::string msg = " : Event was released";
		std::string nl = "\n";

		fwrite(msg.c_str(), 1, msg.size(), m_pFile);
		fwrite(nl.c_str(), 1, nl.size(), m_pFile);

		++m_Msgs;
	}
	catch (...) 
	{
		fclose(m_pFile);
		assert("Couldnt Write to logger");
	}
}

void EventLogger::EventKept()
{
	// Exception handling is used just to be safe.
	try 
	{
		std::string msg = " : Event wasnt released";
		std::string nl = "\n";

		fwrite(msg.c_str(), 1, msg.size(), m_pFile);
		fwrite(nl.c_str(), 1, nl.size(), m_pFile);
		
		++m_Msgs;
	} 
	catch (...) 
	{
		fclose(m_pFile);
		assert("Couldnt Write to logger");
	}
}

// Get & Set Functions
unsigned int EventLogger::numMessagesWritten()
{
	return m_Msgs;
}