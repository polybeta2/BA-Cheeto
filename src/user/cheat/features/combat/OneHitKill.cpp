#include "pch.h"
#include "OneHitKill.h"

#include "core/events/event_manager.h"

namespace cheat::features
{
    OneHitKill::OneHitKill()
        : FeatureBase("One Hit Kill", "Enemies die in one hit",
                      FeatureSection::Combat)
    {
    }
}
