#include "pch.h"
#include "SkipBattleSummary.h"

namespace cheat::features
{
    SkipBattleSummary::SkipBattleSummary()
        : FeatureBase("Skip Battle Summary", "Skips the end battle summary screen",
                      FeatureSection::Game)
    {
        HookManager::install(BattleSceneHandler::Update(), BattleSceneHandler_Update_Hook);
    }

    void SkipBattleSummary::BattleSceneHandler_Update_Hook(BattleSceneHandler* _this)
    {
        if (s_instance->isEnabled())
        {
            if (_this->currentState() == BattleSceneState_Enum::Ending)
            {
                _this->currentState(BattleSceneState_Enum::ShowResult);
                _this->BattleResultSkipType(BattleResultSkipType_Enum::SkipTimeline);
            }
        }

        CALL_ORIGINAL(BattleSceneHandler_Update_Hook, _this);
    }
}
