#pragma once

#include "Renderer.h"
#include <SDL2/SDL_ttf.h>

class Texture {
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;
public:
    Texture() = default;
    explicit Texture(SDL_Texture* texture);
    Texture(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, const SDL_Color &color);
    SDL_Texture* getSDLTexture();
    int getWidth() const;
    int getHeight() const;
    ~Texture();
};
