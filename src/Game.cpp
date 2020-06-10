#include "Game.h"
#include <SDL2/SDL_image.h>

void Game::initSystems() {
    SDL_Init(SDL_INIT_VIDEO);

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
            VIEW_WIDTH * SCALE,
            VIEW_HEIGHT * SCALE,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    SDL_RenderSetLogicalSize(renderer, VIEW_WIDTH, VIEW_HEIGHT);
    SDL_RenderSetScale(renderer, SCALE, SCALE);

    character = loadTexture("/home/rijad/Projects/roguelike/images/character.png");
}

void Game::unInitSystems() {
    SDL_DestroyTexture(character);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
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

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_Rect charRect = { 0, 0, UNIT, UNIT };
        SDL_RenderCopy(renderer, character, nullptr, &charRect);

        SDL_RenderPresent(renderer);
    }
    return 0;
}

SDL_Texture* Game::loadTexture(const std::string &path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(!loadedSurface) {
        SDL_Log("Error: %s", SDL_GetError());
        return nullptr;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(!newTexture) {
        SDL_Log("Error: %s", SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);
    return newTexture;
}
