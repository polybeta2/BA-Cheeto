#include "pch.h"
#include "DumbEnemies.h"

#include "appdata/types.h"

bool DumbEnemies::hCanBeTargeted(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot)
{
    // TODO: Enable field, GUI, etc.
    if (_this->TacticEntityType() == TacticEntityType_Enum::Student)
        return false;
    
    // LOG_INFO("hCanBeTargeted called for BattleEntity at %p with attacker at %p", _this, attacker);
    // LOG_INFO("TacticalEntityType: %s", magic_enum::enum_name(_this->TacticEntityType()).data());
    // LOG_INFO("HitPoint %d", _this->HitPoint()); // can be used for god mode i think
    // LOG_INFO("HitPointBefore %d", _this->HitPointBefore()); // can be used for god mode i think
    // LOG_INFO("MaxHPCapGauge %d", _this->MaxHPCapGauge());
    // LOG_INFO("SummonedTime %d", _this->SummonedTime());
    
	return CALL_ORIGINAL(hCanBeTargeted, _this, attacker, skillSlot);
}

void DumbEnemies::init()
{
    // TODO modularize this. im just busy rn
    HookManager::install(BattleEntity::CanBeTargeted(), hCanBeTargeted);
    LOG_INFO("DumbEnemies feature initialized successfully.");
}
