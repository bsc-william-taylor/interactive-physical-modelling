
#pragma once

#include "IEvent.h"

class EventLogger
{
    std::string path;
    FILE* file;
    int count;
public:
    EventLogger(std::string);
    ~EventLogger();

    void writeEventLog(IEvent*);
    void writeReleasedEvent();
    void writeKeptEvent();

    int getLogsCount();
};