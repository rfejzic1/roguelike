#pragma once

#include <SDL2/SDL.h>
#include "Renderer.h"
#include "InputHandler.h"

class GameEngine {
    SDL_Window* window = nullptr;
    Renderer* renderer = nullptr;
    InputHandler* inputHandler = nullptr;

public:
    GameEngine(int width, int height, int scale = 1);
    Renderer& getRenderer();
    InputHandler& getInputHandler();
    ~GameEngine();
};


