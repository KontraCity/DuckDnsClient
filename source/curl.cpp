#include "curl.hpp"

namespace kc {

size_t StringWriter(char* data, size_t itemSize, size_t itemCount, std::string* target)
{
    target->insert(target->end(), data, data + itemCount);
    return (itemSize * itemCount);
}

Curl::Response Curl::Get(const std::string& url)
{
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl(curl_easy_init(), curl_easy_cleanup);
    if (!curl.get())
        throw std::runtime_error("kc::Curl::Get(): Couldn't initialize Curl: curl_easy_init() failed");

    Response response;
    CURLcode result = curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    if (result != CURLE_OK)
    {
        throw std::runtime_error(fmt::format(
            "kc::Curl::Get(): Couldn't configure request URL: curl_easy_setopt() returned {0}",
            static_cast<int>(result)
        ));
    }
    result = curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response.data);
    if (result != CURLE_OK)
    {
        throw std::runtime_error(fmt::format(
            "kc::Curl::Get(): Couldn't configure request write target: curl_easy_setopt() returned {0}",
            static_cast<int>(result)
        ));
    }
    result = curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, &StringWriter);
    if (result != CURLE_OK)
    {
        throw std::runtime_error(fmt::format(
            "kc::Curl::Get(): Couldn't configure request write function: curl_easy_setopt() returned {0}",
            static_cast<int>(result)
        ));
    }

    result = curl_easy_perform(curl.get());
    if (result != CURLE_OK)
    {
        if (result == CURLE_COULDNT_RESOLVE_HOST || result == CURLE_COULDNT_CONNECT)
            throw std::invalid_argument("kc::Curl::Get(): Couldn't resolve host: internet connection appears to be absent");

        throw std::runtime_error(fmt::format(
            "kc::Curl::Get(): Couldn't perform request: curl_easy_perform() returned {0}",
            static_cast<int>(result)
        ));
    }

    result = curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &response.code);
    if (result != CURLE_OK)
    {
        throw std::runtime_error(fmt::format(
            "kc::Curl::Get(): Couldn't retrieve response code: curl_easy_getinfo() returned {0}",
            static_cast<int>(result)
        ));
    }

    return response;
}

} // namespace kc
