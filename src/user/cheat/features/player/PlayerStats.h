#pragma once
#include "user/cheat/feature_base.h"

struct BasisPoint;

namespace cheat::features
{
    class PlayerStats : public FeatureBase
    {
        DECL_SINGLETON(PlayerStats)

    public:
        PlayerStats();

        void draw() override;

    private:
        std::unordered_map<StatType_Enum, int> m_statValues;
        std::string m_searchFilter;

        std::vector<StatType_Enum> getFilteredStats() const;
        void applyStats(BattleEntityStat* entityStat, BattleEntity* battleEntity) const;

        static void hNewNormalAttackAction_Update(NewNormalAttackAction* _this, Battle* battle);
    };
}
