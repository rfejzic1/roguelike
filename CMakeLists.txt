cmake_minimum_required(VERSION 3.16)
project(roguelike)

set(CMAKE_CXX_STANDARD 17)

add_executable(roguelike main.cpp)

include_directories("/usr/include")
target_link_libraries(roguelike "/usr/lib/libSDL2.so" "/usr/lib/libSDL2_image.so")
