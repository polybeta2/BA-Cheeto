#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class InstantWin : public FeatureBase<InstantWin>
    {
        DECL_SINGLETON(InstantWin)

    public:
        InstantWin();

    private:
        static void Battle_Update_Hook(Battle* _this);
    };
}
