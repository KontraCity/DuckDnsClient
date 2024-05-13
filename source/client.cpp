#include "client.hpp"

namespace kc {

std::unique_ptr<Client> Client::Instance(new Client);

std::time_t Client::SecondsTillNextHour()
{
    constexpr std::time_t secondsInHour = 60 * 60;
    constexpr std::time_t secondsInDay = secondsInHour * 24;

    std::time_t epochSeconds = std::time(nullptr);
    std::time_t daySeconds = epochSeconds - (epochSeconds / secondsInDay * secondsInDay);
    std::time_t hourSeconds = daySeconds - (daySeconds / secondsInHour * secondsInHour);

    return (secondsInHour - hourSeconds);
}

void Client::SignalHandler(int signal)
{
    Client::Instance->m_cv.notify_one();
}

Client::Client()
    : m_logger(Utility::CreateLogger("client"))
{
    // Bind signal handler to handle SIGUSR1 signal
    std::signal(SIGUSR1, SignalHandler);
}

std::string Client::UpdateDdns()
{
    Curl::Response apiResponse;
    bool retried = false;
    while (true)
    {
        try
        {
            apiResponse = Curl::Get(m_config->url());
            break;
        }
        catch (const std::invalid_argument&)
        {
            if (!retried)
            {
                retried = true;
                m_logger.warn("Couldn't access Duck DNS API: no internet connection. Retrying...");
            }

            Utility::Sleep(60);
        }
    }
    if (apiResponse.code != 200)
    {
        throw std::runtime_error(fmt::format(
            "kc::Client::UpdateDdns(): Couldn't update DDNS: API request failed: {}, \"{}\"",
            apiResponse.code,
            apiResponse.data
        ));
    }

    if (retried)
        m_logger.info("Successfully accessed Duck DNS API: internet connection restored");

    std::smatch matches;
    if (!std::regex_search(apiResponse.data, matches, std::regex(R"((\w+)\n([\d\.]+)\n\n(\w+))")))
    {
        throw std::runtime_error(fmt::format(
            "kc::Client::UpdateDdns(): Couldn't parse API response: response is \"{}\"",
            apiResponse.data
        ));
    }
    if (matches.str(1) != "OK")
    {
        throw std::runtime_error(fmt::format(
            "kc::Client::UpdateDdns(): Couldn't update DDNS: API response status is \"{}\"",
            matches.str(1)
        ));
    }

    if (matches.str(3) == "NOCHANGE")
        return {};
    return matches.str(2);
}

void Client::clientLoop(const std::shared_ptr<Config>& config)
{
    m_config = config;
    {
        std::string updatedIp = UpdateDdns();
        if (!updatedIp.empty())
            m_logger.info("Initially updated DDNS to \"{}\"", updatedIp);
    }

    while (true)
    {
        std::unique_lock lock(m_mutex);
        bool force = (m_cv.wait_for(lock, std::chrono::seconds(SecondsTillNextHour())) == std::cv_status::no_timeout);
        std::string updatedIp = UpdateDdns();

        if (force)
        {
            if (!updatedIp.empty())
                m_logger.info("Forcefully updated DDNS to \"{}\"", updatedIp);
            else
                m_logger.info("Tried to forcefully update DDNS, but IP didn't change");
            continue;
        }

        if (!updatedIp.empty())
            m_logger.info("Updated DDNS to \"{}\"", updatedIp);
    }
}

} // namespace kc
