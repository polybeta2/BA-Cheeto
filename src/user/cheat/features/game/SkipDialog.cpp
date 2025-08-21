#include "pch.h"
#include "SkipDialog.h"

namespace cheat::features
{
    SkipDialog::SkipDialog()
        : FeatureBase("Skip Dialog", "Instantly skips dialogs - scenarios, chapters, episodes",
                      FeatureSection::Game)
    {
        HookManager::install(UIScenarioNew::OnEnable(), UIScenarioNew_OnEnable_Hook);
        HookManager::install(UIScenarioNew::OnDisable(), UIScenarioNew_OnDisable_Hook);
        m_updateConnection = EventManager::onUpdate.connect<&SkipDialog::update>(this);
    }

    void SkipDialog::update()
    {
        // Running this on update since I couldn't find a method that runs while scenario is active
        // and users can just enable this feature while in dialog mode
        if (!isEnabled()) return;
        if (m_scenarioTask == nullptr || !m_inScenario) return;

        SAFE_EXECUTE(ScenarioTask::FinishScenario()(m_scenarioTask);)
    }

    void SkipDialog::UIScenarioNew_OnEnable_Hook(UIScenarioNew* _this)
    {
        CALL_ORIGINAL(UIScenarioNew_OnEnable_Hook, _this);
        s_instance->m_scenarioTask = UIScenarioNew::get_Task()(_this);
        s_instance->m_inScenario = true;
    }

    void SkipDialog::UIScenarioNew_OnDisable_Hook(UIScenarioNew* _this)
    {
        CALL_ORIGINAL(UIScenarioNew_OnDisable_Hook, _this);
        s_instance->m_inScenario = false;
        s_instance->m_scenarioTask = nullptr;
    }
}
