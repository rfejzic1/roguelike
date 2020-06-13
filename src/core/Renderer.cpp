#include "Renderer.h"
#include "Texture.h"
#include "GameEngine.h"

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
    render(texture, nullptr, dest, false);
}

void Renderer::render(Texture *texture, Rect *src, Rect *dest, bool flipped) {
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

    SDL_RendererFlip flip = flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture->getSDLTexture(), srcRectPtr, destRectPtr, 0, nullptr, flip);
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

void Renderer::setGameEngine(GameEngine *engine) {
    gameEngine = engine;
}

double Renderer::getFPS() const {
    return gameEngine->getFPS();
}
