#include "GameEngine.h"

#include <SDL2/SDL_image.h>

GameEngine::GameEngine(int width, int height, int scale) {
    if(!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO)) {
        SDL_Init(SDL_INIT_VIDEO);
    }

    // Initialize image loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Log( "Error: %s", IMG_GetError());
        return;
    }

    window = SDL_CreateWindow(
            "roguelike",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width * scale,
            height * scale,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = new Renderer(window, width, height, scale);
    inputHandler = new InputHandler();
}

GameEngine::~GameEngine() {
    if(window) {
        delete renderer;
        delete inputHandler;
        SDL_DestroyWindow(window);
        inputHandler = nullptr;
        renderer = nullptr;
        window = nullptr;
    }
    SDL_Quit();
}

Renderer& GameEngine::getRenderer() {
    return *renderer;
}

InputHandler &GameEngine::getInputHandler() {
    return *inputHandler;
}
