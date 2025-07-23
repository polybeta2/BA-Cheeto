#include "pch.h"
#include "cheat.h"

#include "FeatureManager.h"

#include "features/player/NoCost.h"

#include "features/combat/DumbEnemies.h"
#include "features/combat/OneHitKill.h"

#include "features/debug/Debug.h"

void cheat::init()
{
    auto& manager = FeatureManager::getInstance();

    manager.registerFeatures<
        features::Debug,
        features::NoCost,
        features::DumbEnemies,
        features::OneHitKill
    >();

    manager.init();
}

void cheat::update()
{
    FeatureManager::getInstance().update();
}
