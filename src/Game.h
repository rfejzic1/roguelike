#pragma once

#include <SDL2/SDL.h>

class Game {
    bool isRunning = true;
    SDL_Window* window = nullptr;

    void initSystems();
    void unInitSystems();
public:
    Game();
    int run();
    ~Game();
};
