#include "pch.h"
#include "cheat.h"

#include "FeatureManager.h"
#include "features/NoCost.h"
#include "features/DumbEnemies.h"

using namespace cheat::features;

void cheat::init()
{
    auto& manager = FeatureManager::getInstance();

    manager.registerFeatures<
        NoCost,
        DumbEnemies
    >();

    manager.init();
}

void cheat::update()
{
    FeatureManager::getInstance().update();
}
