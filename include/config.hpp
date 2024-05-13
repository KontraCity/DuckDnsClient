#pragma once

// STL modules
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

namespace kc {

namespace ConfigConst
{
    // Client configuration file path
    constexpr const char* ConfigFile = "/etc/duckdnsclient.conf";

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
    // Shared config instance pointer
    using Pointer = std::shared_ptr<Config>;

    // Configuration file read/parse error
    class Error : public std::logic_error
    {
    public:
        using logic_error::logic_error;
    };

private:
    std::vector<std::string> m_domains;
    std::string m_token;
    std::string m_url;

public:
    /// @brief Generate sample configuration file for user to fill out
    /// @throw std::runtime_error if file couldn't be created
    static void GenerateSampleFile();

public:
    /// @brief Read and parse configuration file
    /// @throw Config::Error if reading/parsing error occurs
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
