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
    render(texture, nullptr, dest);
}

void Renderer::render(Texture *texture, Rect *src, Rect *dest) {
    SDL_Rect srcRect;
    SDL_Rect destRect;

    if(src) {
        srcRect = { src->x, src->y, src->width, src->height };
    }
    if(dest) {
        destRect = { dest->x, dest->y, dest->width, dest->height };
    }

    SDL_Rect* srcRectPtr = src ? &srcRect : nullptr;
    SDL_Rect* destRectPtr = dest ? &destRect : nullptr;

    SDL_RenderCopy(renderer, texture->getSDLTexture(), srcRectPtr, destRectPtr);
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
