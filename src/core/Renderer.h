#pragma once

#include <SDL2/SDL.h>
#include "Rect.h"

class Texture;

class Renderer {
    const int VIEW_WIDTH;
    const int VIEW_HEIGHT;
    const int SCALE;

    SDL_Renderer* renderer = nullptr;

    explicit Renderer(SDL_Window* window, int viewWidth, int viewHeight, int scale = 1);
    SDL_Renderer* getSDLRenderer();
public:
    void clear();
    void render(Texture *texture, Rect *dest);
    void update();
    ~Renderer();
    friend class GameEngine;
};