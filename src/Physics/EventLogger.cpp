
#include "EventLogger.h"
#include <assert.h>

EventLogger::EventLogger(std::string filename) :
    path(filename),
    count(NULL)
{
    std::string title = "\n - Event Logger - \n\n";
    fopen_s(&file, path.c_str(), "w+");
    fseek(file, 0, SEEK_SET);
    fwrite(title.c_str(), 1, title.size(), file);
}

EventLogger::~EventLogger()
{
    fclose(file);
}

void EventLogger::writeEventLog(IEvent * event)
{
    auto msg = event->getMessage();
    fwrite(msg.c_str(), 1, msg.size(), file);
}

void EventLogger::writeReleasedEvent()
{
    std::string msg = " : Event was released \n";
    fwrite(msg.c_str(), 1, msg.size(), file);
    count++;
}

void EventLogger::writeKeptEvent()
{
    std::string msg = " : Event wasnt released \n";
    fwrite(msg.c_str(), 1, msg.size(), file);
    count++;
}

int EventLogger::getLogsCount()
{
    return count;
}