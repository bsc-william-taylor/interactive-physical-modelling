
#include "EventManager.h"

EventManager * EventManager::eventManager = 0;

EventManager::EventManager()
    : eventLogger("log.txt")
{
}

EventManager::~EventManager()
{
}

void EventManager::triggerEvent(IEvent * event, bool destroy, void * data)
{
    if (event != NULL)
    {
        eventLogger.writeEventLog(event);
        event->onTriggered(data);

        if (destroy)
        {
            eventLogger.writeReleasedEvent();
            delete(event);
        }
    }
}

void EventManager::triggerEvent(int ms, IEvent * event, void * data)
{
    auto newEvent = new TimedEvent();
    newEvent->timer = new Win32Timer();
    newEvent->timer->Start();
    newEvent->event = event;
    newEvent->data = data;
    newEvent->ms = ms;

    timedEvents.push_back(newEvent);
}

void EventManager::updateManager()
{
    std::vector<TimedEvent*> toRemove;

    for (auto& timedEvent : timedEvents)
    {
        timedEvent->timer->Stop();

        if (timedEvent->timer->Difference(TimeType::MS) >= timedEvent->ms)
        {
            timedEvent->event->onTriggered(timedEvent->data);
            toRemove.push_back(timedEvent);
        }
    }

    for (auto& event : toRemove)
    {
        const auto begin = timedEvents.begin();
        const auto end = timedEvents.end();

        timedEvents.erase(std::remove(begin, end, event), end);

        SAFE_RELEASE(event->timer);
        SAFE_RELEASE(event->event);
        SAFE_RELEASE(event);
    }
}

EventManager * EventManager::get()
{
    if (!eventManager)
    {
        eventManager = new EventManager();
    }

    return eventManager;
}