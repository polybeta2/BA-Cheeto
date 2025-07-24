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

    void GodMode::onEnable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s enabled", getName().c_str());
    }

    void GodMode::onDisable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s disabled", getName().c_str());
    }
}
