#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class NoCost : public FeatureBase
    {
        DECL_SINGLETON(NoCost)

    public:
        NoCost();

        bool init() override;
        void draw() override;

        void onEnable() override;
        void onDisable() override;

    private:
        static void hProcessSkillCard(PlayerSkillCardManager* _this);
    };
}
