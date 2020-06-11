#pragma once

#include <SDL2/SDL.h>
#include "Renderer.h"

class Window {
    SDL_Window* window = nullptr;
    Renderer* renderer = nullptr;

public:
    Window(int width, int height, int scale = 1);
    Renderer& getRenderer();
    ~Window();
};


