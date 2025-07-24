#include "pch.h"
#include "event_manager.h"

inline Event<> EventManager::onUpdate;

// TODO: Improve Event system
inline Event<> EventManager::onOneHitKillEnabled;
inline Event<> EventManager::onOneHitKillDisabled;
inline Event<> EventManager::onGodModeEnabled;
inline Event<> EventManager::onGodModeDisabled;