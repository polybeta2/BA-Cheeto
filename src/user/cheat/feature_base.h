#pragma once

#include "core/config/config_field.h"
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
            , m_allowDraw(section != FeatureSection::Hooks && section != FeatureSection::Count)
            , m_enabledField("Unknown", name, "enabled", false)
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
        bool isEnabled() const { return m_enabledField.get(); }

        void setEnabled(bool enabled)
        {
            bool currentState = m_enabledField.get();
            if (currentState == enabled) return;

            m_enabledField = enabled;

            if (enabled)
            {
                onEnable();
            }
            else
            {
                onDisable();
            }
        }

        bool isAllowDraw() const { return m_allowDraw; }

        void setupConfig(const char* sectionName)
        {
            if (!sectionName) return;

            m_enabledField = Config::Field(sectionName, m_name, "enabled", false);

            if (m_enabledField.get()) onEnable();
        }

    protected:
        std::string m_name;
        std::string m_description;
        FeatureSection m_section;
        bool m_allowDraw;
        bool m_hasEnabledField;
        Config::Field<bool> m_enabledField{};
    };
}
