#include "pch.h"
#include "PlayerStats.h"

#include "core/events/event_manager.h"

namespace cheat::features
{
    PlayerStats::PlayerStats()
        : FeatureBase("Player Stats", "Modify your character's stats", FeatureSection::Player)
    {
        // Alternatively, you can find a better function to hook as long as it gets called every update
        HookManager::install(NewNormalAttackAction::Update(), NewNormalAttackAction_Update_Hook);
        m_reloadConnection = EventManager::onReloadConfig.connect<&PlayerStats::onReloadConfig>(this);
    }

    void PlayerStats::init()
    {
        createStatFields();
        loadStatsFromConfig();
    }

    void PlayerStats::draw()
    {
        ImGui::InputText("Search Stats", &m_searchFilter);
        ImGui::SameLine();

        if (ImGui::Button("Reset All"))
        {
            resetAllStats();
        }

        if (ImGui::BeginChild("StatsList", ImVec2(0, 340), true))
        {
            auto filteredStats = getFilteredStats();

            for (auto stat : filteredStats)
            {
                const char* statName = magic_enum::enum_name(stat).data();

                if (!m_statValues.contains(stat))
                {
                    m_statValues[stat] = 0;
                }

                int currentValue = m_statValues[stat];
                if (ImGui::InputInt(statName, &currentValue))
                {
                    if (currentValue != m_statValues[stat])
                    {
                        m_statValues[stat] = currentValue;

                        if (auto it = m_statFields.find(stat); it != m_statFields.end())
                        {
                            it->second.field->set(currentValue);
                        }
                    }
                }
            }
        }
        ImGui::EndChild();
    }

    void PlayerStats::createStatFields()
    {
        m_statFields.clear();

        // Create a config field for each stat type
        for (auto stat = StatType_Enum::MaxHP; stat < StatType_Enum::Max;
             stat = static_cast<StatType_Enum>(static_cast<int>(stat) + 1))
        {
            const std::string key = std::string("stat_") + std::string(magic_enum::enum_name(stat));

            StatField statField;
            statField.field = std::make_unique<config::Field<int>>(this->getPath(), key, 0);

            statField.connection = statField.field->onChanged(
                [this, stat](const int& oldVal, const int& newVal)
                {
                    // LOG_DEBUG("Stat {} changed from {} to {}",
                    //           magic_enum::enum_name(stat), oldVal, newVal);

                    // Update local cache
                    if (newVal != 0)
                    {
                        m_statValues[stat] = newVal;
                    }
                    else
                    {
                        m_statValues.erase(stat);
                    }
                });
            
            // LOG_DEBUG("Field val {}", field.get()->get());
            m_statFields[stat] = std::move(statField);
        }
    }

    void PlayerStats::loadStatsFromConfig()
    {
        m_statValues.clear();

        for (const auto& [stat, field] : m_statFields)
        {
            int value = field.field->get();
            if (value != 0)
            {
                // LOG_DEBUG("Loading {} stat with value {}", magic_enum::enum_name(stat), value);
                m_statValues[stat] = value;
            }
        }
    }

    void PlayerStats::resetAllStats()
    {
        for (auto& [stat, value] : m_statValues)
        {
            value = 0;
        }

        for (const auto& [stat, field] : m_statFields)
        {
            field.field->set(0);
        }

        m_statValues.clear();

        LOG_INFO("Reset all player stats to default values");
    }

    std::vector<StatType_Enum> PlayerStats::getFilteredStats() const
    {
        std::vector<StatType_Enum> filtered;

        for (auto stat = StatType_Enum::MaxHP; stat < StatType_Enum::Max;
             stat = static_cast<StatType_Enum>(static_cast<int>(stat) + 1))
        {
            if (m_searchFilter.empty())
            {
                filtered.push_back(stat);
            }
            else
            {
                std::string statName = magic_enum::enum_name(stat).data();
                std::ranges::transform(statName, statName.begin(), tolower);

                std::string searchLower = m_searchFilter;
                std::ranges::transform(searchLower, searchLower.begin(), tolower);

                if (statName.find(searchLower) != std::string::npos)
                {
                    filtered.push_back(stat);
                }
            }
        }

        return filtered;
    }

    void PlayerStats::applyStats(BattleEntityStat* entityStat, BattleEntity* battleEntity) const
    {
        for (const auto& [stat, value] : m_statValues)
        {
            if (value != 0)
            {
                BattleEntityStatProcessor::Apply()(battleEntity->statProcessor(), stat);
                BattleEntityStat::SetValue()(entityStat, stat, static_cast<int64_t>(value));

                auto currentStat = battleEntity->statProcessor()->CurrentStat();
                battleEntity->statProcessor()->InitialStat(currentStat);
                battleEntity->statProcessor()->DefaultStat(currentStat);

                if (stat == StatType_Enum::MaxHP)
                {
                    BattleEntity::SetHitPoint()(battleEntity, value);
                }
            }
        }
    }

    void PlayerStats::NewNormalAttackAction_Update_Hook(NewNormalAttackAction* _this, Battle* battle)
    {
        if (s_instance->isEnabled())
        {
            auto executer = _this->Executer();
            if (executer->TacticEntityType() == TacticEntityType_Enum::Student)
            {
                if (const auto entityStat = executer->get_CurrentStat()(_this->Executer());
                    entityStat != nullptr)
                {
                    s_instance->applyStats(entityStat, _this->Executer());
                }
            }
        }

        CALL_ORIGINAL(NewNormalAttackAction_Update_Hook, _this, battle);
    }

    void PlayerStats::onReloadConfig()
    {
        // LOG_DEBUG("Reloading PlayerStats config...");
        loadStatsFromConfig();
    }
}
