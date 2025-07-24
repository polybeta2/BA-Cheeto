#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class InstantWin : public FeatureBase
    {
        DECL_SINGLETON(InstantWin)

    public:
        InstantWin();

    private:
        static void hBattle_Update(Battle* _this);
    };
}
