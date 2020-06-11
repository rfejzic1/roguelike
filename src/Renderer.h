#pragma once

#include <SDL2/SDL.h>

class Renderer {
    const int VIEW_WIDTH;
    const int VIEW_HEIGHT;
    const int SCALE;

    SDL_Renderer* renderer = nullptr;
    explicit Renderer(SDL_Window* window, int viewWidth, int viewHeight, int scale = 1);
public:
    void clear();
    void render(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* destrect);
    void update();
    // TODO: Remove getSDLRenderer later
    SDL_Renderer* getSDLRenderer();
    ~Renderer();
    friend class Window;
};
