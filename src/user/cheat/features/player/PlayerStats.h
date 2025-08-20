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
        struct StatField
        {
            std::unique_ptr<config::Field<int>> field;
            config::Field<int>::Connection connection;

            StatField() = default;

            StatField(StatField&& other) noexcept
                : field(std::move(other.field))
                , connection(std::move(other.connection))
            {
            }

            StatField& operator=(StatField&& other) noexcept
            {
                if (this != &other)
                {
                    field = std::move(other.field);
                    connection = std::move(other.connection);
                }
                return *this;
            }

            StatField(const StatField&) = delete;
            StatField& operator=(const StatField&) = delete;
        };

        std::unordered_map<StatType_Enum, int> m_statValues;
        std::unordered_map<StatType_Enum, StatField> m_statFields;

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
