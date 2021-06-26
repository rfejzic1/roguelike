cmake_minimum_required(VERSION 3.16)
project(roguelike)

set(CMAKE_CXX_STANDARD 17)

file(GLOB proj_src
        "src/*.h"
        "src/*.cpp"
        "src/core/*.h"
        "src/core/*.cpp"
        "src/actions/*.h"
        "src/actions/*.cpp"
        )

add_executable(roguelike main.cpp ${proj_src})

include_directories("/usr/include")
target_link_libraries(roguelike "/usr/lib/libSDL2.so" "/usr/lib/libSDL2_image.so" "/usr/lib/libSDL2_ttf.so")
