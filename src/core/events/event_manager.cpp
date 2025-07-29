#include "pch.h"
#include "event_manager.h"

inline Event<> EventManager::onUpdate;

EventManager::EventManager() = default;

EventManager::~EventManager()
{
    shutdown();
}

EventManager& EventManager::getInstance()
{
    static EventManager instance;
    return instance;
}

void EventManager::shutdown()
{
    onUpdate.clear();
}
