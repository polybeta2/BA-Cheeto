#pragma once
#include "feature_base.h"

namespace cheat
{
    class FeatureManager
    {
    public:
        static FeatureManager& getInstance();

        template <typename... Arg>
        void registerFeatures()
        {
            (registerFeature(std::make_unique<Arg>()), ...);
        }

        void init();
        void draw();

        void reloadConfig();

        FeatureBase* getFeature(const std::string& name);
        std::vector<FeatureBase*> getFeaturesBySection(FeatureSection section);

    private:
        FeatureManager() = default;
        std::vector<std::unique_ptr<FeatureBase>> m_features;
        std::unordered_map<std::string, FeatureBase*> m_featureMap;

        void registerFeature(std::unique_ptr<FeatureBase> feature);

        static const char* getSectionName(FeatureSection section);
        static void helpMarker(const char* desc);

        void onKeyDown(int vk, bool& handled) const;

        // Event<int, bool&>::Connection m_keyDownConnection;
    };
}
