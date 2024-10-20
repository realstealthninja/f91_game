cmake_minimum_required(VERSION 3.30)
project(game_thing VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(game_thing src/main.cpp)
target_link_libraries(game_thing sfml-graphics)

file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
