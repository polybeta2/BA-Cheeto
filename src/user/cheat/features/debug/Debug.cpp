#include "pch.h"
#include "Debug.h"

namespace cheat::features
{
    Debug::Debug()
        : FeatureBase("Debug", "Debug features for development",
                      FeatureSection::Debug)
        , m_test0(false)
    {
        // HookManager::install(Battle::Update(), hBattle_Update);
        // HookManager::install(BattleEntity::ApplyStat(), hBattleEntity_ApplyStat);
        // HookManager::install(BattleEntityStatProcessor::Apply(), hBattleEntityStatProcessor_Apply);
        // HookManager::install(Character::ApplyDamage(), hCharacter_ApplyDamage);

        HookManager::install(Character::Update(), hCharacter_Update);
        HookManager::install(Character::InitAmmo(), hCharacter_InitAmmo);
        HookManager::install(Character::ReloadAmmo(), hCharacter_ReloadAmmo);

        // HookManager::install(NewNormalAttackAction::Update(), hNewNormalAttackAction_Update);
    }

    void Debug::draw()
    {
        ImGui::Checkbox("Test 0", &m_test0);
    }

    void Debug::hBattle_Update(Battle* _this)
    {
        if (s_instance->isEnabled())
        {
        }

        CALL_ORIGINAL(hBattle_Update, _this);
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

    void Debug::hCharacter_Update(Character* _this, Battle* battle)
    {
        if (s_instance->isEnabled())
        {
            // if (_this->TacticEntityType() == TacticEntityType_Enum::Student)
            // {
            //     LOG_DEBUG("Update Character: bulletType: %s, bulletCount: %d",
            //               _this->BulletType(), _this->BulletCount());
            // }
        }

        CALL_ORIGINAL(hCharacter_Update, _this, battle);
    }

    void* Debug::hCharacter_ApplyDamage(Character* _this, BattleEntity* attacker, DamageResult damageResult)
    {
        if (s_instance->isEnabled())
        {
            LOG_DEBUG(
                "isAttacked: %s attacker: %s, attackPower: %d, damage: %d, criticalMultiplier: %f, hitResultType: %s",
                _this->IsAttacked() ? "true" : "false",
                attacker->Name()->ToString().c_str(),
                damageResult.AttackPower(),
                damageResult.Damage(),
                damageResult.CriticalMultiplier(),
                magic_enum::enum_name(damageResult.HitResultType()).data());
        }

        return CALL_ORIGINAL(hCharacter_ApplyDamage, _this, attacker, damageResult);
    }

    void Debug::hCharacter_InitAmmo(Character* _this)
    {
        if (s_instance->m_test0)
        {
            LOG_DEBUG("InnitAmmo");
            LOG_DEBUG("bullet type: %s, bullet count: %d",
                      magic_enum::enum_name(_this->BulletType()).data(),
                      _this->BulletCount());
        }

        CALL_ORIGINAL(hCharacter_InitAmmo, _this);
    }

    void Debug::hCharacter_ReloadAmmo(Character* _this)
    {
        if (s_instance->m_test0)
        {
            LOG_DEBUG("ReloadAmmo");
            LOG_DEBUG("bullet type: %s, bullet count: %d",
                      magic_enum::enum_name(_this->BulletType()).data(),
                      _this->BulletCount());

            auto currentStat = UNITY_CALL(BattleEntity::get_CurrentStat, _this)
            if (currentStat == nullptr)
                CALL_ORIGINAL(hCharacter_ReloadAmmo, _this);

            auto bulletCount = UNITY_CALL(BattleEntityStat::get_Item, currentStat, StatType_Enum::MaxBulletCount)
            _this->BulletCount(bulletCount);

            return;
        }

        CALL_ORIGINAL(hCharacter_ReloadAmmo, _this);
    }

    void Debug::hNewNormalAttackAction_Update(NewNormalAttackAction* _this, Battle* battle)
    {
        if (s_instance->m_test0)
        {
            if (_this->actionState() == ActionState_Enum::Phase01)
            {
                LOG_DEBUG(
                    "NewNormalAttackAction Update: %s, Executer: %s, attackReloadDuration: %d, elapsed: %d, duration: %d",
                    magic_enum::enum_name(_this->BehaviorType()).data(),
                    _this->Executer()->Name()->ToString().c_str(),
                    _this->attackReloadDuration(),
                    _this->elapsed(),
                    _this->duration());
                return;
            }
        }

        CALL_ORIGINAL(hNewNormalAttackAction_Update, _this, battle);
    }
}
