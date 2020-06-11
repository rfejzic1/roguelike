cmake_minimum_required(VERSION 3.16)
project(roguelike)

set(CMAKE_CXX_STANDARD 17)

add_executable(roguelike main.cpp src/Game.cpp src/Game.h src/Renderer.cpp src/Renderer.h src/GameEngine.cpp src/GameEngine.h src/InputHandler.cpp src/InputHandler.h src/Timer.cpp src/Timer.h src/AssetManager.h src/TextureManager.cpp src/TextureManager.h src/Texture.cpp src/Texture.h)

include_directories("/usr/include")
target_link_libraries(roguelike "/usr/lib/libSDL2.so" "/usr/lib/libSDL2_image.so")
