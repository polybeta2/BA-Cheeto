#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class PlayerStats : public FeatureBase<PlayerStats>
    {
        DECL_SINGLETON(PlayerStats)

    public:
        PlayerStats();

        void init() override;
        void draw() override;

    private:
        std::unordered_map<StatType_Enum, int> m_statValues;
        std::unordered_map<StatType_Enum, std::unique_ptr<config::Field<int>>> m_statFields;

        std::string m_searchFilter;

        Event<>::Connection m_reloadConnection;

        void createStatFields();
        void loadStatsFromConfig();
        void resetAllStats();
        std::vector<StatType_Enum> getFilteredStats() const;
        void applyStats(BattleEntityStat* entityStat, BattleEntity* battleEntity) const;

        static void hNewNormalAttackAction_Update(NewNormalAttackAction* _this, Battle* battle);

        void onReloadConfig();
    };
}
