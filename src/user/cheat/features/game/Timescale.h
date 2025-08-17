#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class Timescale : public FeatureBase
    {
        DECL_SINGLETON(Timescale)

    public:
        Timescale();

        void draw() override;

    private:
        static void hBattleGameTime_Tick(BattleGameTime* _this);

        Config::Field<float> m_scaleField;
        float m_scale;
    };
}
