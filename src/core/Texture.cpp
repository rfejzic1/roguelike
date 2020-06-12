#include "Texture.h"

Texture::Texture(SDL_Texture *texture) : texture(texture) {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

SDL_Texture *Texture::getSDLTexture() {
    return texture;
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}
