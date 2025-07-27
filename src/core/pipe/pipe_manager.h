#pragma once

class PipeManager
{
public:
    static PipeManager& getInstance();

    void start();
    void stop();

    bool isFeatureEnabled(const std::string& featureName) const;
    void setFeatureState(const std::string& featureName, bool enabled);

    // Prevent copying
    PipeManager(const PipeManager&) = delete;
    PipeManager& operator=(const PipeManager&) = delete;

    // Prevent moving
    PipeManager(PipeManager&&) = delete;
    PipeManager& operator=(PipeManager&&) = delete;

private:
    PipeManager();
    ~PipeManager();

    void runServer();
    void handleClient(HANDLE hPipe);

    std::atomic<bool> m_running{false};
    std::thread m_serverThread;
    std::unordered_map<std::string, bool> m_features;

    static constexpr auto PIPE_NAME = L"\\\\.\\pipe\\cunny_pipe00";
};
