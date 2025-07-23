#include "pch.h"
#include "cheat.h"

#include "features/NoCost.h"
#include "features/DumbEnemies.h"

void cheat::init()
{
    // TODO: Call feature manager and register all features here
    features::NoCost::getInstance()->init();
    features::DumbEnemies::getInstance()->init();
}
