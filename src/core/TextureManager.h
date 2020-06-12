#pragma once

#include <SDL2/SDL.h>
#include "AssetManager.h"
#include "Texture.h"

class GameEngine;

class TextureManager : public AssetManager<Texture> {
    SDL_Renderer* renderer = nullptr;
    Texture* loader(const std::string &uri) override;
    explicit TextureManager(SDL_Renderer *renderer);
public:
    friend class GameEngine;
};
