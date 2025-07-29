#include "pch.h"
#include "cheat.h"

#include "feature_manager.h"

#include "features/debug/Debug.h"

#include "features/player/NoCost.h"
#include "features/player/GodMode.h"
#include "features/player/PlayerStats.h"

#include "features/combat/DumbEnemies.h"
#include "features/combat/OneHitKill.h"

#include "features/game/InstantWin.h"

#include "features/hooks/BattleEntityHook.h"

void cheat::init()
{
    auto& manager = FeatureManager::getInstance();

    manager.registerFeatures<
        // features::Debug,

        // Cheat features
        features::NoCost,
        features::GodMode,
        features::PlayerStats,
        features::DumbEnemies,
        features::OneHitKill,
        features::InstantWin,

        // Hooks
        features::BattleEntityHook
    >();

    manager.init();
}

void cheat::shutdown()
{
    auto& hookManager = HookManager::getInstance();
    hookManager.shutdown();
}
