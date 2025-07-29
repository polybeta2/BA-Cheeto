#pragma once
#include "event.h"

class EventManager
{
public:
    static EventManager& getInstance();

    static Event<> onUpdate;
    static Event<> onBattleFinalize;

    static void shutdown();

private:
    EventManager();
    ~EventManager();
};
