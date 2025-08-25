#include "pch.h"
#include "SkipDialog.h"

namespace cheat::features
{
    SkipDialog::SkipDialog()
        : FeatureBase("Skip Dialog", "Instantly skips dialogs - scenarios, chapters, episodes",
                      FeatureSection::Game)
    {
        UIScenarioNew::OnEnable_Hook().set(UIScenarioNew_OnEnable_Hook);
        UIScenarioNew::OnDisable_Hook().set(UIScenarioNew_OnDisable_Hook);
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
        UIScenarioNew::OnEnable_Hook().call(_this);
        s_instance->m_scenarioTask = UIScenarioNew::get_Task()(_this);
        s_instance->m_inScenario = true;
    }

    void SkipDialog::UIScenarioNew_OnDisable_Hook(UIScenarioNew* _this)
    {
        UIScenarioNew::OnDisable_Hook().call(_this);
        s_instance->m_inScenario = false;
        s_instance->m_scenarioTask = nullptr;
    }
}
