### --- Initial configuration --- ###
cmake_minimum_required(VERSION 3.10)
project(DuckDnsClient VERSION 1.1)

# Set CXX version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


### --- Executable configuration --- ###
add_executable(DuckDnsClient
    "source/client.cpp"
    "source/config.cpp"
    "source/curl.cpp"
    "source/main.cpp"
    "source/utility.cpp"
)
target_include_directories(DuckDnsClient PRIVATE "include/")


### --- Libraries configuration --- ###
target_link_libraries(DuckDnsClient
    "fmt"
    "curl"
    "pthread"
)

# Library spdlog
find_package(spdlog REQUIRED)
target_link_libraries(DuckDnsClient spdlog::spdlog)
