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

Texture *Texture::createFromText(Renderer *renderer, TTF_Font *font, const std::string &text, const Color &color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(!textSurface) {
        SDL_Log("Error: %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), textSurface);
    SDL_FreeSurface(textSurface);

    if(!texture) {
        SDL_Log("Error: %s", TTF_GetError());
        return nullptr;
    }
    return new Texture(texture);
}
