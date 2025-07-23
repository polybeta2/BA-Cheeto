#pragma once
#include "event.h"

class EventManager
{
public:
    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    static Event<> onUpdate;

private:
    EventManager() = default;
    ~EventManager() = default;
};
