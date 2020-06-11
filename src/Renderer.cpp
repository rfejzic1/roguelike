#include "Renderer.h"

Renderer::Renderer(SDL_Window* window, int viewWidth, int viewHeight, int scale)
    : VIEW_WIDTH(viewWidth), VIEW_HEIGHT(viewHeight), SCALE(scale)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    SDL_RenderSetLogicalSize(renderer, VIEW_WIDTH, VIEW_HEIGHT);
    SDL_RenderSetScale(renderer, SCALE, SCALE);
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

void Renderer::render(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *destrect) {
    SDL_RenderCopy(renderer, texture, srcrect, destrect);
}

void Renderer::update() {
    SDL_RenderPresent(renderer);
}

Renderer::~Renderer() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}

SDL_Renderer *Renderer::getSDLRenderer() {
    return renderer;
}
