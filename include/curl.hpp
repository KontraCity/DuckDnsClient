#pragma once

// STL modules
#include <string>
#include <memory>
#include <stdexcept>

// Library Curl
#include <curl/curl.h>

// Library {fmt}
#include <fmt/format.h>

namespace kc {

namespace Curl
{
    struct Response
    {
        std::string data;
        long code = -1;
    };

    /// @brief Perform HTTP GET request
    /// @param url Request URL
    /// @throw std::runtime_error if internal error occurs
    /// @throw std::invalid_argument if couldn't connect to server
    Response Get(const std::string& url);
}

} // namespace kc
