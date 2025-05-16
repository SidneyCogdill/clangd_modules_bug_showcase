cmake_minimum_required(VERSION 3.30)

project(clangd_modules_bug_showcase LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(proxy)
include(ProxyModule.cmake)

add_executable(clangd_modules_bug_showcase main.cpp)

target_sources(clangd_modules_bug_showcase PRIVATE
    FILE_SET CXX_MODULES
    FILES
        proxy.cpp
)

target_link_libraries(
    clangd_modules_bug_showcase
    PRIVATE
    msft_proxy::module
)
