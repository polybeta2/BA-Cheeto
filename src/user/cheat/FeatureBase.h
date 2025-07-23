#pragma once

#include "utils/singleton.h"

namespace cheat
{
    enum class FeatureSection
    {
        Player,
        Combat,
        Settings,
        COUNT
    };
    
    class FeatureBase
    {
    public:
        FeatureBase(const std::string& name, const std::string& description, FeatureSection section)
            : m_name(name), m_description(description), m_section(section), m_enabled(false)
        {
        }
    
        virtual ~FeatureBase() = default;

        virtual bool init() = 0;
        virtual void draw() = 0;

        virtual void update() {}
        virtual void onEnable() {}
        virtual void onDisable() {}

        const std::string& getName() const { return m_name;}
        const std::string& getDescription() const { return m_description; }
        FeatureSection getSection() const { return m_section; }
        bool isEnabled() const { return m_enabled; }

        void setEnabled(bool enabled)
        {
            if (m_enabled != enabled)
            {
                m_enabled = enabled;
                if (m_enabled)
                {
                    onEnable();
                }
                else
                {
                    onDisable();
                }
            }
        }

    protected:
        std::string m_name;
        std::string m_description;
        FeatureSection m_section;
        bool m_enabled;
    };
}
