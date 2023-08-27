cmake_minimum_required(VERSION 3.10)

project(Maze)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Maze src/sdl-test.cpp)
target_link_libraries(Maze ${SDL2_LIBRARIES})
