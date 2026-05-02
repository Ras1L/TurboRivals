cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(RAYLIB_DIR ${CMAKE_SOURCE_DIR}/external/raylib-5.5)
set(ENET_DIR ${CMAKE_SOURCE_DIR}/external/enet)
set(BULLET_DIR ${CMAKE_SOURCE_DIR}/external/bullet3-3.25)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui-1.92.7)
set(RLIMGUI_DIR ${CMAKE_SOURCE_DIR}/external/rlImGui-Raylib_5_5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME TurboRivals)
project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(${RAYLIB_DIR})
add_subdirectory(${ENET_DIR})
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
add_subdirectory(${BULLET_DIR})
add_subdirectory(${IMGUI_DIR})
add_subdirectory(${RLIMGUI_DIR})
add_subdirectory(${SOURCE_DIR})
