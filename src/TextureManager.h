#pragma once

#include <SDL2/SDL.h>
#include "AssetManager.h"
#include "Texture.h"

class GameEngine;

class TextureManager : public AssetManager<Texture> {
    GameEngine& engine;
    Texture* loader(const std::string &uri) override;
public:
    explicit TextureManager(GameEngine& gameEngine);
    friend class GameEngine;
};
