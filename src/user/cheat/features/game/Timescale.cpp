#include "pch.h"
#include "Timescale.h"

namespace cheat::features
{
    Timescale::Timescale()
        : FeatureBase("Timescale", "Speed up battle by scaling logic time per tick", FeatureSection::Game)
    {
        HookManager::install(BattleGameTime::Tick(), BattleGameTime_Tick_Hook);
    }

    void Timescale::draw()
    {
        ImGui::SliderFloat("Scale", &*m_scaleField.ref(), 0.1f, 10.0f, "%.2fx");
        ImGui::SameLine();
        if (ImGui::Button("Reset")) m_scaleField.set(1.0f);
        ImGui::TextDisabled("Affects battle logic tick; 2.0x ~ twice as fast");
    }

    void Timescale::BattleGameTime_Tick_Hook(BattleGameTime* _this)
    {
        if (s_instance->isEnabled())
        {
            const float scale = std::clamp(s_instance->m_scaleField.get(), 0.1f, 10.0f);

            const float oldLogicSecPerFrame = _this->LogicSecondPerFrame();
            const int32_t oldCurrentFrame = _this->CurrentFrame();

            _this->LogicSecondPerFrame(oldLogicSecPerFrame / scale);

            CALL_ORIGINAL(BattleGameTime_Tick_Hook, _this);

            _this->LogicSecondPerFrame(oldLogicSecPerFrame);

            if (_this->CurrentFrame() < oldCurrentFrame)
            {
                _this->CurrentFrame(oldCurrentFrame);
            }

            return;
        }

        CALL_ORIGINAL(BattleGameTime_Tick_Hook, _this);
    }
}
