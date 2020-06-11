#include "Window.h"

#include <SDL2/SDL_image.h>

Window::Window(int width, int height, int scale) {
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
}

Window::~Window() {
    if(window) {
        delete renderer;
        SDL_DestroyWindow(window);
        renderer = nullptr;
        window = nullptr;
    }
    SDL_Quit();
}

Renderer& Window::getRenderer() {
    return *renderer;
}
