#include "Renderer.h"
#include "Texture.h"

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

void Renderer::render(Texture *texture, Rect *dest) {
    SDL_Rect rect = { dest->x, dest->y, dest->width, dest->height };
    SDL_RenderCopy(renderer, texture->getSDLTexture(), nullptr, &rect);
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
