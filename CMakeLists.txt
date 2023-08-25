cmake_minimum_required(VERSION 3.10)

project(SDLTest)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(SDLTest src/sdl-test.cpp)
target_link_libraries(SDLTest ${SDL2_LIBRARIES})
