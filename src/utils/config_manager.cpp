#include "pch.h"
#include "config_manager.h"
#include "utils/logger.h"

ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

std::string ConfigManager::configPath() const {
    char* appData = nullptr;
    size_t len = 0;
    _dupenv_s(&appData, &len, "APPDATA");
    std::filesystem::path base = appData ? appData : ".";
    if (appData) free(appData);

    std::filesystem::path dir = base / "Cunny";
    std::error_code ec;
    if (!std::filesystem::exists(dir, ec)) {
        std::filesystem::create_directories(dir, ec);
        if (ec) LOG_ERROR("Failed to create config directory: {}", ec.message().c_str());
    }
    return (dir / "config.json").string();
}

bool ConfigManager::load() {
    const auto path = configPath();
    std::ifstream f(path);
    if (!f.good()) {
        m_data = nlohmann::json{ {"version", 1}, {"features", nlohmann::json::object()} };
        return true;
    }
    try {
        f >> m_data;
        if (!m_data.contains("features")) m_data["features"] = nlohmann::json::object();
        return true;
    } catch (const std::exception& e) {
        LOG_ERROR("Failed to parse config: {}", e.what());
        m_data = nlohmann::json{ {"version", 1}, {"features", nlohmann::json::object()} };
        return false;
    }
}

bool ConfigManager::save() {
    const auto path = configPath();
    try {
        std::ofstream f(path, std::ios::trunc);
        f << m_data.dump(2);
        return true;
    } catch (const std::exception& e) {
        LOG_ERROR("Failed to save config: {}", e.what());
        return false;
    }
}

const nlohmann::json* ConfigManager::getFeatureNodeConst(const std::string& section, const std::string& name) const {
    auto itF = m_data.find("features");
    if (itF == m_data.end() || !itF->is_object()) return nullptr;
    auto itS = itF->find(section);
    if (itS == itF->end() || !itS->is_object()) return nullptr;
    auto itN = itS->find(name);
    if (itN == itS->end() || !itN->is_object()) return nullptr;
    return &*itN;
}

nlohmann::json* ConfigManager::getFeatureNode(const std::string& section, const std::string& name) {
    auto itF = m_data.find("features");
    if (itF == m_data.end() || !itF->is_object()) return nullptr;
    auto itS = itF->find(section);
    if (itS == itF->end() || !itS->is_object()) return nullptr;
    auto itN = itS->find(name);
    if (itN == itS->end() || !itN->is_object()) return nullptr;
    return &*itN;
}

nlohmann::json& ConfigManager::getOrCreateFeatureNode(const std::string& section, const std::string& name) {
    if (!m_data.contains("features") || !m_data["features"].is_object()) m_data["features"] = nlohmann::json::object();
    auto& features = m_data["features"];
    if (!features.contains(section) || !features[section].is_object()) features[section] = nlohmann::json::object();
    auto& sec = features[section];
    if (!sec.contains(name) || !sec[name].is_object()) sec[name] = nlohmann::json::object();
    return sec[name];
}

bool ConfigManager::getFeatureEnabled(const std::string& section, const std::string& name, bool def) const {
    const auto* node = getFeatureNodeConst(section, name);
    if (!node) return def;
    auto it = node->find("enabled");
    if (it == node->end()) return def;
    try { return it->get<bool>(); } catch (...) { return def; }
}

void ConfigManager::setFeatureEnabled(const std::string& section, const std::string& name, bool enabled) {
    auto& node = getOrCreateFeatureNode(section, name);
    node["enabled"] = enabled;
}
