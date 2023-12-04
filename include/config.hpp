#pragma once

// STL modules
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

namespace kc {

namespace ConfigConst
{
    // Configuration file path
    constexpr const char* ConfigFilePath = "/etc/duckdnsclient.conf";

    namespace Tags
    {
        // Represents one or more domains to update
        constexpr const char* Domains = "Domains";

        // Represents domain update token
        constexpr const char* Token = "Token";
    }
}

class Config
{
public:
    class Error : public std::invalid_argument
    {
    public:
        using invalid_argument::invalid_argument;
    };

private:
    std::vector<std::string> m_domains;
    std::string m_token;
    std::string m_url;

public:
    /// @brief Generate default configuration file
    /// @throw std::runtime_error if internal error occurs
    static void GenerateDefaultFile();

public:
    /// @brief Parse config file
    /// @throw Config::Error if config parsing error occurs
    Config();

    /// @brief Get DDNS update domains
    /// @return DDNS update domains
    const std::vector<std::string>& domains() const
    {
        return m_domains;
    }

    /// @brief Get DDNS update token
    /// @return DDNS update token
    const std::string& token() const
    {
        return m_token;
    }

    /// @brief Get DDNS update URL
    /// @return DDNS update URL
    const std::string& url() const
    {
        return m_url;
    }
};

} // namespace kc
