
#pragma once

#include "EventLogger.h"
#include "Win32Timer.h"
#include "IEvent.h"

class EventManager
{
    struct TimedEvent
    {
        Win32Timer* timer;
        IEvent* event;
        void* data;
        int ms;
    };

    static EventManager * eventManager;
    vector<TimedEvent *> timedEvents;
    EventLogger eventLogger;
public:
    EventManager();
    ~EventManager();

    void triggerEvent(int, IEvent*, void*);
    void triggerEvent(IEvent*, bool, void*);
    void updateManager();

    static EventManager* get();
};