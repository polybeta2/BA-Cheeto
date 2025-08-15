#pragma once

#include "utils/singleton.h"

namespace cheat
{
    enum class FeatureSection
    {
        Player,
        Combat,
        Game,
        Settings,
        Debug,
        Hooks,
        Count
    };

    class FeatureBase
    {
    public:
        FeatureBase(const std::string& name, const std::string& description, FeatureSection section)
            : m_name(name)
            , m_description(description)
            , m_section(section)
            , m_enabled(false)
            , m_allowDraw(section != FeatureSection::Hooks && section != FeatureSection::Count)
        {
        }

        virtual ~FeatureBase() = default;

        virtual void init()
        {
        }

        virtual void draw()
        {
        }

        virtual void onEnable()
        {
            LOG_INFO("{} enabled", getName().c_str());
        }

        virtual void onDisable()
        {
            LOG_INFO("{} disabled", getName().c_str());
        }

        const std::string& getName() const { return m_name; }
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

        bool isAllowDraw() const { return m_allowDraw; }

    protected:
        std::string m_name;
        std::string m_description;
        FeatureSection m_section;
        bool m_enabled;
        bool m_allowDraw;
    };
}
