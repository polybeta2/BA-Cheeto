#include "pch.h"
#include "GodMode.h"

#include "core/events/event_manager.h"

namespace cheat::features
{
    GodMode::GodMode()
        : FeatureBase("God Mode", "Makes player invincible",
                      FeatureSection::Player)
    {
    }
}
