## --- Project configuration --- ##
cmake_minimum_required(VERSION 3.10)
project(DuckDnsClient VERSION 1.1)

## --- Compiler configuration --- ##
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
include_directories("include/")

## --- Packages configuration --- ##
find_package(fmt CONFIG REQUIRED)
find_package(CURL REQUIRED)

## --- Executable configuration --- ##
add_executable(DuckDnsClient
    "source/client.cpp"
    "source/config.cpp"
    "source/curl.cpp"
    "source/main.cpp"
    "source/utility.cpp"
)
target_link_libraries(DuckDnsClient
    fmt::fmt
    CURL::libcurl
    "pthread"
)
