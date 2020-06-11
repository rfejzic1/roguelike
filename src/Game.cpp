#include "Game.h"
#include <SDL2/SDL_image.h>

Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    character = loadTexture("/home/rijad/Projects/roguelike/images/character.png");
}

Game::~Game() {
    SDL_DestroyTexture(character);
}

Renderer &Game::getRenderer() {
    return engine.getRenderer();
}

int Game::run() {

    int x = 0, y = 0;

    engine.getInputHandler().on("right", [&x]() {
        x += 1;
    });
    engine.getInputHandler().on("left", [&x]() {
        x -= 1;
    });
    engine.getInputHandler().on("up", [&y]() {
        y -= 1;
    });
    engine.getInputHandler().on("down", [&y]() {
        y += 1;
    });

    while(isRunning) {
        isRunning = engine.getInputHandler().pollInputs();

        getRenderer().clear();

        SDL_Rect charRect = { x * UNIT, y * UNIT, UNIT, UNIT };
        getRenderer().render(character, nullptr, &charRect);

        getRenderer().update();
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

    newTexture = SDL_CreateTextureFromSurface(engine.getRenderer().getSDLRenderer(), loadedSurface);
    if(!newTexture) {
        SDL_Log("Error: %s", SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);
    return newTexture;
}
