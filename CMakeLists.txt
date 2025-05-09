cmake_minimum_required(VERSION 3.30)

project(clangd_modules_bug_showcase LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(clangd_modules_bug_showcase main.cpp)

target_sources(clangd_modules_bug_showcase
  PRIVATE
    FILE_SET CXX_MODULES FILES
      unique_wrapper.cpp
      unique_fd.cpp
      my_app.cpp
)

