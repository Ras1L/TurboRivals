cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib-5.5_linux_amd64)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME TurboRivals)
project(${PROJECT_NAME} LANGUAGES CXX)


add_subdirectory(src)