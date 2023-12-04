#pragma once

// STL modules
#include <thread>
#include <chrono>

namespace kc {

namespace Utility
{
    /// @brief Stop execution for some time
    /// @param seconds Seconds to stop execution for
    void Sleep(size_t seconds);
}

} // namespace kc
