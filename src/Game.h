#pragma once

#include <string>
#include "Window.h"

class Game {
    bool isRunning = true;
    Window window;
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
