#pragma once
#include "user/cheat/feature_base.h"
#include "utils/config_manager.h"

struct BasisPoint;

namespace cheat::features
{
    class PlayerStats : public FeatureBase
    {
        DECL_SINGLETON(PlayerStats)

    public:
        PlayerStats();

    void init() override;
        void draw() override;

    private:
        std::unordered_map<StatType_Enum, int> m_statValues;
        std::string m_searchFilter;
    void saveStatsToConfig();

        std::vector<StatType_Enum> getFilteredStats() const;
        void applyStats(BattleEntityStat* entityStat, BattleEntity* battleEntity) const;

        static void hNewNormalAttackAction_Update(NewNormalAttackAction* _this, Battle* battle);
    };
}
