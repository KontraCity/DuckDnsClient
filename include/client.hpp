#pragma once

// STL modules
#include <ctime>
#include <csignal>
#include <memory>
#include <regex>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Library spdlog
#include <spdlog/spdlog.h>

// Custom modules
#include "config.hpp"
#include "curl.hpp"
#include "utility.hpp"

namespace kc {

class Client
{
private:
    spdlog::logger m_logger;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::shared_ptr<Config> m_config;

public:
    // Singleton instance
    static std::unique_ptr<Client> Instance;

private:
    /// @brief Get amount of seconds till next hour
    /// @return Amount of seconds till next hour
    static std::time_t SecondsTillNextHour();

    /// @brief Signal handler
    /// @param signal Signal to handle
    static void SignalHandler(int signal);

private:
    /// @brief Initialize Duck DNS client
    Client();

    /// @brief Try to update DDNS
    /// @throw std::runtime_error if internal error occures
    /// @return New IP if updated successfully, empty string if IP didn't change
    std::string UpdateDdns();

public:
    /// @brief Duck DNS client loop
    /// @param config Parsed Duck DNS client config
    void clientLoop(const std::shared_ptr<Config>& config);
};

} // namespace kc
