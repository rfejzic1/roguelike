#include "Renderer.h"
#include "Texture.h"
#include "GameEngine.h"

Renderer::Renderer(SDL_Window* window, int viewWidth, int viewHeight, int scale)
    : VIEW_WIDTH(viewWidth), VIEW_HEIGHT(viewHeight), SCALE(scale), camera()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    SDL_RenderSetLogicalSize(renderer, VIEW_WIDTH, VIEW_HEIGHT);
    SDL_RenderSetScale(renderer, SCALE, SCALE);
    setCamera({});
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

void Renderer::render(Texture *texture, Rect *dest) {
    render(texture, nullptr, dest, false);
}

void Renderer::render(Texture *texture, Rect *src, Rect *dest, bool flipped) {
    Vector2D camPos = camera.getPosition();
    int camOffset = VIEW_WIDTH / 2;

    if(!dest ||
        dest->x < camPos.x - camOffset ||
        dest->x > camPos.x + VIEW_WIDTH + camOffset ||
        dest->y < camPos.y - camOffset ||
        dest->y > camPos.y + VIEW_HEIGHT + camOffset
    ) {
        // do not render; not in view
        return;
    }

    SDL_Rect srcRect;
    SDL_Rect destRect;

    if(src) {
        srcRect = { src->x, src->y, src->width, src->height };
    }
    if(dest) {
        destRect = { dest->x - camPos.x, dest->y - camPos.y, dest->width, dest->height };
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

void Renderer::setCamera(const Camera &newCamera) {
    camera = newCamera;
    camera.setRenderer(this);
}

Camera &Renderer::getCamera() {
    return camera;
}

int Renderer::getViewWidth() {
    return VIEW_WIDTH;
}

int Renderer::getViewHeight() {
    return VIEW_HEIGHT;
}
