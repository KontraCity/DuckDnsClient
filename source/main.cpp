// STL modules
#include <iostream>
#include <memory>

// Library spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Custom modules
#include "config.hpp"
#include "client.hpp"
using namespace kc;

int main(int parameterCount, char** parameterValue)
{
    for (int parameterIndex = 1; parameterIndex < parameterCount; ++parameterIndex)
    {
        std::string parameter = parameterValue[parameterIndex];
        if (parameter == "-h" || parameter == "--help")
        {
            std::cout << fmt::format(
                "Duck DNS client usage: {0} [OPTIONS]\n"
                "Available options:\n"
                "    (No options)\t\tNormally start Duck DNS client\n"
                "    -h, --help\t\t\tDisplay this message and exit\n"
                "    -gc, --generate-config\tGenerate default config and exit\n",
                parameterValue[0]
            );
            return 0;
        }
        else if (parameter == "-gc" || parameter == "--generate-config")
        {
            try
            {
                Config::GenerateDefaultFile();
            }
            catch (const std::runtime_error& error)
            {
                std::cerr << fmt::format("Couldn't open configuration file \"{0}\"! Are you root?\n", ConfigConst::ConfigFilePath);
                return 1;
            }
            
            std::cout << fmt::format(
                "Generated default configuration file \"{0}\".\n"
                "Go ahead and fill created fields.\n",
                ConfigConst::ConfigFilePath
            );
            return 0;
        }
        else
        {
            std::cout << "Unknown option: " << parameter << '\n';
        }
    }
    
    std::shared_ptr<Config> config;
    try
    {
        config = std::make_unique<Config>();
    }
    catch (const Config::Error& error)
    {
        spdlog::critical("Configuration file parsing error: {0}.", error.what());
        spdlog::info("Check configuration file at \"{0}\".", ConfigConst::ConfigFilePath);
        spdlog::info("You can generate default configuration file by running \"{0} --generate-config\"", parameterValue[0]);
        return 1;
    }

    try
    {
        spdlog::info("Ready.");
        Client::Instance->clientLoop(config);
    }
    catch (const std::runtime_error& error)
    {
        spdlog::critical("Runtime error: \"{0}\".", error.what());
        spdlog::critical("Duck DNS client is terminating.");
    }
}
