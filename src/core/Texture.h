#pragma once

#include "Renderer.h"

class Texture {
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;
public:
    Texture() = default;
    explicit Texture(SDL_Texture* texture);
    SDL_Texture* getSDLTexture();
    int getWidth() const;
    int getHeight() const;
    ~Texture();
};
