#pragma once

// STL modules
#include <optional>
#include <thread>
#include <chrono>

// Library spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace kc {

namespace Utility
{
    /// @brief Create a logger
    /// @param name Logger name
    /// @param forceColor Whether to force sinks colors or not
    /// @return Created logger
    spdlog::logger CreateLogger(const std::string& name, std::optional<bool> forceColor = {});

    /// @brief Stop execution for some time
    /// @param seconds Seconds to stop execution for
    void Sleep(size_t seconds);
}

} // namespace kc
