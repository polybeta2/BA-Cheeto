#include "pch.h"
#include "GodMode.h"

namespace cheat::features
{
    GodMode::GodMode()
        : FeatureBase("God Mode", "Makes player invincible",
                      FeatureSection::Player)
    {
    }
}
