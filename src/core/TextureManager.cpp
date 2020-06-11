#include "TextureManager.h"
#include "GameEngine.h"
#include "Renderer.h"

TextureManager::TextureManager(GameEngine& gameEngine) : engine(gameEngine) {}

Texture* TextureManager::loader(const std::string &uri) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(uri.c_str());

    if(!loadedSurface) {
        SDL_Log("Error: %s", SDL_GetError());
        return nullptr;
    }

    // Texture pointer
    newTexture = SDL_CreateTextureFromSurface(engine.getRenderer().getSDLRenderer(), loadedSurface);
    if(!newTexture) {
        SDL_Log("Error: %s", SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);
    return new Texture(newTexture);
}
