#pragma once

#include <string>
#include <SDL2/SDL.h>

class Game {
    bool isRunning = true;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* character = nullptr;

    const int UNIT = 16;
    const int VIEW_HEIGHT = UNIT * 9;
    const int VIEW_WIDTH = UNIT * 16;
    const int SCALE = 4;

    void initSystems();
    void unInitSystems();
    SDL_Texture* loadTexture(const std::string& path);
public:
    Game();
    int run();
    ~Game();
};
