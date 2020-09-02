cmake_minimum_required(VERSION 3.17)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(gameOfLife main.cpp)


target_link_libraries(gameOfLife PRIVATE SDL2)