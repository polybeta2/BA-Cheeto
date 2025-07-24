#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class Debug : public FeatureBase
    {
        DECL_SINGLETON(Debug)

    public:
        Debug();

        void draw() override;

    private:
        bool m_test0;

        static void hBattle_Update(Battle* _this);
        static void hBattleEntity_ApplyStat(BattleEntity* _this, StatType_Enum statType);
        static void hBattleEntityStatProcessor_Apply(BattleEntityStatProcessor* _this, StatType_Enum statType);
        static void* hCharacter_ApplyDamage(Character* _this, BattleEntity* attacker, DamageResult damageResult);

        static void hCharacter_Update(Character* _this, Battle* battle);
        static void hCharacter_InitAmmo(Character* _this);
        static void hCharacter_ReloadAmmo(Character* _this);

        static void hNewNormalAttackAction_Update(NewNormalAttackAction* _this, Battle* battle);
    };
}
