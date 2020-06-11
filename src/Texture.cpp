#include "Texture.h"

Texture::Texture(SDL_Texture *texture) : texture(texture) {}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

SDL_Texture *Texture::getSDLTexture() {
    return texture;
}
