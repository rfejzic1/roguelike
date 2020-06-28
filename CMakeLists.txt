cmake_minimum_required(VERSION 3.16)
project(roguelike)

set(CMAKE_CXX_STANDARD 17)

add_executable(roguelike main.cpp src/Game.cpp src/Game.h src/core/Renderer.cpp src/core/Renderer.h src/core/GameEngine.cpp src/core/GameEngine.h src/core/InputHandler.cpp src/core/InputHandler.h src/core/Timer.cpp src/core/Timer.h src/core/AssetManager.h src/core/TextureManager.cpp src/core/TextureManager.h src/core/Texture.cpp src/core/Texture.h src/core/Rect.h src/core/Sprite.cpp src/core/Sprite.h src/core/Vector2D.h src/core/SpriteAnimator.cpp src/core/SpriteAnimator.h src/core/Camera.cpp src/core/Camera.h src/Map.cpp src/Map.h src/Matrix.h src/MapBuilder.cpp src/MapBuilder.h src/core/SpriteAtlas.cpp src/core/SpriteAtlas.h src/TileSet.cpp src/TileSet.h src/core/Renderable.h src/Entity.cpp src/Entity.h src/Hero.cpp src/Hero.h src/actions/Action.h src/actions/MoveAction.cpp src/actions/MoveAction.h src/actions/PlayerInputAction.cpp src/actions/PlayerInputAction.h src/Monster.cpp src/Monster.h src/TurnManager.cpp src/TurnManager.h src/GameManager.cpp src/GameManager.h src/actions/Direction.h src/MapObject.cpp src/MapObject.h)

include_directories("/usr/include")
target_link_libraries(roguelike "/usr/lib/libSDL2.so" "/usr/lib/libSDL2_image.so")
