#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class SkipDialog : public FeatureBase<SkipDialog>
    {
        DECL_SINGLETON(SkipDialog)

    public:
        SkipDialog();

        void update() override;

    private:
        static void UIScenarioNew_OnEnable_Hook(UIScenarioNew* _this);
        static void UIScenarioNew_OnDisable_Hook(UIScenarioNew* _this);

        ScenarioTask* m_scenarioTask = nullptr;
        std::atomic<bool> m_inScenario{false};

        FastEvent<>::Connection m_updateConnection;
    };
}
