#pragma once

#include <SDL2/SDL.h>
#include "Renderer.h"
#include "InputHandler.h"

class GameEngine {
    bool isRunning = true;
    SDL_Window* window = nullptr;
    Renderer* renderer = nullptr;
    InputHandler* inputHandler = nullptr;
    double avgFPS = 0;

    static const int SCREEN_FPS = 120;
    static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

public:
    GameEngine(int width, int height, int scale = 1);
    void loop(const std::function<void(double)>& loopFunction);
    Renderer& getRenderer();
    InputHandler& getInputHandler();
    double getFPS();
    ~GameEngine();
};


