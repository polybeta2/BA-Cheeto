#include "pch.h"
#include "cheat.h"

#include "features/NoCost.h"
#include "features/DumbEnemies.h"

void Cheat::init()
{
    NoCost::init();
    DumbEnemies::init();
}
