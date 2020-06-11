#pragma once

#include <string>
#include "GameEngine.h"
#include "Timer.h"

class Game {
    GameEngine engine;
    SDL_Texture* character = nullptr;

    static const int UNIT = 16;
    static const int VIEW_HEIGHT = UNIT * 9;
    static const int VIEW_WIDTH = UNIT * 16;
    static const int SCALE = 4;

    Renderer& getRenderer();
    SDL_Texture* loadTexture(const std::string& path);
public:
    Game();
    int run();
    ~Game();
};
