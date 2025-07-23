#include "pch.h"
#include "FeatureManager.h"

namespace cheat
{
    FeatureManager& FeatureManager::getInstance()
    {
        static FeatureManager instance;
        return instance;
    }

    void FeatureManager::registerFeature(std::unique_ptr<FeatureBase> feature)
    {
        const std::string& name = feature->getName();
        m_featureMap[name] = feature.get();
        m_features.push_back(std::move(feature));
    }

    void FeatureManager::init()
    {
        LOG_INFO("Initializing %zu features", m_features.size());

        for (const auto& feature : m_features)
        {
            try
            {
                if (feature->init())
                {
                    LOG_INFO("Feature '%s' initialized successfully", feature->getName().c_str());
                }
                else
                {
                    LOG_ERROR("Failed to initialize feature '%s'", feature->getName().c_str());
                }
            }
            catch (const std::exception& e)
            {
                LOG_ERROR("Exception during initialization of feature '%s': %s", feature->getName().c_str(), e.what());
            }
        }
    }

    void FeatureManager::update()
    {
        for (const auto& feature : m_features)
        {
            if (feature->isEnabled())
            {
                try
                {
                    // TODO: Maybe use an event and hook feature->update() to GameMain_Update to run with the game loop
                    feature->update();
                }
                catch (const std::exception& e)
                {
                    LOG_ERROR("Exception during update of feature '%s': %s", feature->getName().c_str(), e.what());
                }
            }
        }
    }

    void FeatureManager::draw()
    {
        if (ImGui::BeginTabBar("FeatureTabs", ImGuiTabBarFlags_None))
        {
            for (auto sectionIdx = 0; sectionIdx < static_cast<int>(FeatureSection::COUNT); ++sectionIdx)
            {
                auto section = static_cast<FeatureSection>(sectionIdx);
                auto sectionFeatures = getFeaturesBySection(section);
                if (!sectionFeatures.empty()) continue;

                if (ImGui::BeginTabItem(getSectionName(section)))
                {
                    ImGui::Spacing();

                    for (auto* feature : sectionFeatures)
                    {
                        bool enabled = feature->isEnabled();
                        if (ImGui::Checkbox(("##" + feature->getName()).c_str(), &enabled))
                        {
                            feature->setEnabled(enabled);
                        }

                        ImGui::SameLine();
                        ImGui::Text("%s", feature->getName().c_str());

                        // Help marker with description
                        if (!feature->getDescription().empty())
                        {
                            ImGui::SameLine();
                            helpMarker(feature->getDescription().c_str());
                        }

                        // Feature-specific controls (indented)
                        if (enabled)
                        {
                            ImGui::Indent(20.0f);
                            feature->draw();
                            ImGui::Unindent(20.0f);
                        }

                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::Spacing();
                    }

                    ImGui::EndTabItem();
                }
            }

            ImGui::EndTabBar();
        }
    }

    FeatureBase* FeatureManager::getFeature(const std::string& name)
    {
        const auto it = m_featureMap.find(name);
        return it != m_featureMap.end() ? it->second : nullptr;
    }

    std::vector<FeatureBase*> FeatureManager::getFeaturesBySection(FeatureSection section)
    {
        std::vector<FeatureBase*> features;
        for (const auto& feature : m_features)
        {
            if (feature->getSection() == section)
            {
                features.push_back(feature.get());
            }
        }
        return features;
    }

    const char* FeatureManager::getSectionName(FeatureSection section)
    {
        switch (section)
        {
            case FeatureSection::Player:
                return "Player";
            case FeatureSection::Combat:
                return "Combat";
            case FeatureSection::Settings:
                return "Settings";
            default:
                return "Unknown";
        }
    }

    void FeatureManager::helpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
}
