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

    // TODO: Improve Event system
    static Event<> onOneHitKillEnabled;
    static Event<> onOneHitKillDisabled;
    static Event<> onGodModeEnabled;
    static Event<> onGodModeDisabled;

private:
    EventManager() = default;
    ~EventManager() = default;
};
