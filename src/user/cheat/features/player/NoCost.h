#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class NoCost : public FeatureBase<NoCost>
    {
        DECL_SINGLETON(NoCost)

    public:
        NoCost();

    private:
        static void PlayerSkillCardManager_ProcessSkillCard_Hook(PlayerSkillCardManager* _this);
    };
}
