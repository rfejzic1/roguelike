#include "Texture.h"

Texture::Texture(SDL_Texture *texture) : texture(texture) {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

Texture::Texture(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, const SDL_Color &color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if(!textSurface) {
        SDL_Log("Error: %s", TTF_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(!texture) {
            SDL_Log("Error: %s", TTF_GetError());
        } else {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
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
