#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class NoCost : public FeatureBase
    {
        DECL_SINGLETON(NoCost)

    public:
        NoCost();

        void onEnable() override;
        void onDisable() override;

    private:
        static void hPlayerSkillCardManager_ProcessSkillCard(PlayerSkillCardManager* _this);
    };
}
