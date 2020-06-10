#include "Game.h"

void Game::initSystems() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("roguelike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_SHOWN);
}

void Game::unInitSystems() {
    if(window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

Game::Game() {
    initSystems();
}

Game::~Game() {
    unInitSystems();
}

int Game::run() {
    SDL_Event e;
    while(isRunning) {
        while(SDL_PollEvent(&e) != 0) {
            if( e.type == SDL_QUIT ) {
                isRunning = false;
            }
        }
    }
    return 0;
}
