cmake_minimum_required(VERSION 3.20)
project(mosaic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(MOSAIC_USE_LUAJIT "Use LuaJIT instead of Lua 5.4 if available" OFF)

# Find SDL2 and Lua; Point CMake at package manager toolchain if needed
find_package(SDL2 REQUIRED)
if (MOSAIC_USE_LUAJIT)
    find_package(LuaJIT)
endif()

# Prefer imported targets. Fall back to FindLua variables only if needed.
if (LUAJIT_FOUND)
    message(STATUS "Using LuaJIT")
endif()

add_executable(mosaic
    src/main.cpp
    src/Engine.cpp
    src/Time.cpp
    src/Input.cpp
    src/Renderer.cpp
    src/ScriptSystem.cpp
)

# SDL2 from vcpkg exposes imported targets
target_link_libraries(mosaic PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Lua: try LuaJIT target first, then Lua::Lua, then variables
if (TARGET LuaJIT::LuaJIT)
    target_link_libraries(mosaic PRIVATE LuaJIT::LuaJIT)
elseif (TARGET Lua::Lua)
    target_link_libraries(mosaic PRIVATE Lua::Lua)
else()
    find_package(Lua 5.4 REQUIRED)
    target_include_directories(mosaic PRIVATE src ${LUA_INCLUDE_DIR})
    target_link_libraries(mosaic PRIVATE ${LUA_LIBRARIES})
endif()
