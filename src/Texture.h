#pragma once

#include "Renderer.h"

class Texture {
    SDL_Texture* texture = nullptr;
public:
    Texture() = default;
    explicit Texture(SDL_Texture* texture);
    SDL_Texture* getSDLTexture();
    ~Texture();
};
