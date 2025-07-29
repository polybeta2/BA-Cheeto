#include "pch.h"
#include "Debug.h"

namespace cheat::features
{
    Debug::Debug()
        : FeatureBase("Debug", "Debug features for development",
                      FeatureSection::Debug)
        , m_test0(false)
    {
        // HookManager::install(BattleEntity::ApplyStat(), hBattleEntity_ApplyStat);
        // HookManager::install(BattleEntityStatProcessor::Apply(), hBattleEntityStatProcessor_Apply);
        // HookManager::install(Character::ApplyDamage(), hCharacter_ApplyDamage);
    }

    void Debug::draw()
    {
        ImGui::Checkbox("Test 0", &m_test0);
    }

    void Debug::hBattleEntity_ApplyStat(BattleEntity* _this, StatType_Enum statType)
    {
        if (s_instance->isEnabled())
        {
            LOG_DEBUG("hBattleEntity_ApplyStat: name=%s, entityType=%s, %s",
                      _this->Name()->ToString().c_str(),
                      magic_enum::enum_name(_this->TacticEntityType()).data(),
                      magic_enum::enum_name(statType).data());
        }

        CALL_ORIGINAL(hBattleEntity_ApplyStat, _this, statType);
    }

    void Debug::hBattleEntityStatProcessor_Apply(BattleEntityStatProcessor* _this, StatType_Enum statType)
    {
        if (s_instance->isEnabled())
        {
            // LOG_DEBUG("hBattleEntityStatProcessor_Apply: entity=%s, statType=%s battlePower=%d",
            //           _this->owner()->Name()->ToString().c_str(),
            //           magic_enum::enum_name(statType).data(),
            //           _this->owner());
        }
        CALL_ORIGINAL(hBattleEntityStatProcessor_Apply, _this, statType);
    }

    void* Debug::hCharacter_ApplyDamage(Character* _this, BattleEntity* attacker, DamageResult damageResult)
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

        return CALL_ORIGINAL(hCharacter_ApplyDamage, _this, attacker, damageResult);
    }
}
