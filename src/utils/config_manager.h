#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <nlohmann/json.hpp>

class ConfigManager {
public:
    static ConfigManager& getInstance();

    bool load();
    bool save();

    // feature path helpers
    bool getFeatureEnabled(const std::string& section, const std::string& name, bool def = false) const;
    void setFeatureEnabled(const std::string& section, const std::string& name, bool enabled);

    template <typename T>
    T getFeatureValue(const std::string& section, const std::string& name, const std::string& key, const T& def) const {
        const nlohmann::json* node = getFeatureNodeConst(section, name);
        if (!node) return def;
        const auto it = node->find(key);
        if (it == node->end()) return def;
        try { return it->get<T>(); } catch (...) { return def; }
    }

    template <typename T>
    void setFeatureValue(const std::string& section, const std::string& name, const std::string& key, const T& value) {
        auto& node = getOrCreateFeatureNode(section, name);
        node[key] = value;
    }

    const nlohmann::json& data() const { return m_data; }

private:
    ConfigManager() = default;

    std::string configPath() const;
    nlohmann::json* getFeatureNode(const std::string& section, const std::string& name);
    const nlohmann::json* getFeatureNodeConst(const std::string& section, const std::string& name) const;
    nlohmann::json& getOrCreateFeatureNode(const std::string& section, const std::string& name);

    nlohmann::json m_data;
};
