#include "pch.h"
#include "cheat.h"

#include "FeatureManager.h"

#include "features/debug/Debug.h"

#include "features/player/NoCost.h"
#include "features/player/GodMode.h"

#include "features/combat/DumbEnemies.h"
#include "features/combat/OneHitKill.h"

#include "features/hooks/BattleEntityHook.h"

void cheat::init()
{
    auto& manager = FeatureManager::getInstance();

    manager.registerFeatures<
        features::Debug,

        // Cheat features
        features::NoCost,
        features::GodMode,
        features::DumbEnemies,
        features::OneHitKill,

        // Hooks
        features::BattleEntityHook
    >();

    manager.init();
}
