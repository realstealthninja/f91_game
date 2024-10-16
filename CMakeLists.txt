cmake_minimum_required(VERSION 3.30)
project(game_thing VERSION 0.0.1)

add_executable(game_thing main.cpp)

target_link_libraries(game_thing raylib)

file(COPY background.png DESTINATION "${CMAKE_BINARY_DIR}")
