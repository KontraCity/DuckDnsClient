#include "utility.hpp"

namespace kc {

void Utility::Sleep(size_t seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

} // namespace kc
