#include "pch.h"
#include "Debug.h"

namespace cheat::features
{
    Debug::Debug()
        : FeatureBase("Debug", "Debug features for development",
                      FeatureSection::Debug)
        , m_test0(false)
    {
        // HookManager::install(BattleEntity::ApplyStat(), BattleEntity_ApplyStat_Hook);
        // HookManager::install(BattleEntityStatProcessor::Apply(), BattleEntityStatProcessor_Apply_Hook);
        // HookManager::install(Character::ApplyDamage(), Character_ApplyDamage_Hook);
    }

    void Debug::draw()
    {
        ImGui::Checkbox("Test 0", &m_test0);
    }

    void Debug::BattleEntity_ApplyStat_Hook(BattleEntity* _this, StatType_Enum statType)
    {
        if (s_instance->isEnabled())
        {
            LOG_DEBUG("BattleEntity_ApplyStat_Hook: name=%s, entityType=%s, %s",
                      _this->Name()->ToString().c_str(),
                      magic_enum::enum_name(_this->TacticEntityType()).data(),
                      magic_enum::enum_name(statType).data());
        }

        CALL_ORIGINAL(BattleEntity_ApplyStat_Hook, _this, statType);
    }

    void Debug::BattleEntityStatProcessor_Apply_Hook(BattleEntityStatProcessor* _this, StatType_Enum statType)
    {
        if (s_instance->isEnabled())
        {
            // LOG_DEBUG("BattleEntityStatProcessor_Apply_Hook: entity=%s, statType=%s battlePower=%d",
            //           _this->owner()->Name()->ToString().c_str(),
            //           magic_enum::enum_name(statType).data(),
            //           _this->owner());
        }
        CALL_ORIGINAL(BattleEntityStatProcessor_Apply_Hook, _this, statType);
    }

    void* Debug::Character_ApplyDamage_Hook(Character* _this, BattleEntity* attacker, DamageResult damageResult)
    {
        if (s_instance->isEnabled())
        {
            // LOG_DEBUG(
            //     "isAttacked: %s attacker: %s, attackPower: %d, damage: %d, criticalMultiplier: %f, hitResultType: %s",
            //     _this->IsAttacked() ? "true" : "false",
            //     attacker->Name()->ToString().c_str(),
            //     damageResult.AttackPower(),
            //     damageResult.Damage(),
            //     damageResult.CriticalMultiplier(),
            //     magic_enum::enum_name(damageResult.HitResultType()).data());
        }

        return CALL_ORIGINAL(Character_ApplyDamage_Hook, _this, attacker, damageResult);
    }
}
