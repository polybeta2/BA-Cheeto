#include "pch.h"
#include "Timescale.h"

namespace cheat::features
{
    // Speeds up battle logic by scaling BattleGameTime::Tick.
    Timescale::Timescale()
        : FeatureBase("Timescale", "Speed up battle by scaling logic time per tick", FeatureSection::Game)
        , m_scaleField("Game", getName(), "scale", 1.0f)
        , m_scale(m_scaleField.get())
    {
        HookManager::install(BattleGameTime::Tick(), hBattleGameTime_Tick);
    }

    void Timescale::draw()
    {
        float prev = m_scale;
        ImGui::SliderFloat("Scale (x)", &m_scale, 0.1f, 10.0f, "%.2fx");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(80.0f);
        if (ImGui::InputFloat("##scale_input", &m_scale, 0.0f, 0.0f, "%.2f"))
        {
            m_scale = std::clamp(m_scale, 0.1f, 10.0f);
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset")) m_scale = 1.0f;
        ImGui::TextDisabled("Affects battle logic tick; 2.0x ~ twice as fast");

        if (m_scale != prev)
        {
            m_scaleField = m_scale;
        }
    }

    void Timescale::hBattleGameTime_Tick(BattleGameTime* _this)
    {
        if (!s_instance->isEnabled())
        {
            CALL_ORIGINAL(hBattleGameTime_Tick, _this);
            return;
        }

        const float scale = std::clamp(s_instance->m_scale, 0.1f, 10.0f);

        const float oldLogicSecPerFrame = _this->LogicSecondPerFrame();
        const int32_t oldCurrentFrame = _this->CurrentFrame();

        _this->LogicSecondPerFrame(oldLogicSecPerFrame / scale);

        CALL_ORIGINAL(hBattleGameTime_Tick, _this);

        _this->LogicSecondPerFrame(oldLogicSecPerFrame);

        if (_this->CurrentFrame() < oldCurrentFrame)
        {
            _this->CurrentFrame(oldCurrentFrame);
        }
    }
}
