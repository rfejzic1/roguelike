#include "SpriteAtlas.h"

#include <utility>

SpriteAtlas::SpriteAtlas(std::shared_ptr<Texture> texture)
    : texture(std::move(texture)) {}

void SpriteAtlas::mark(const std::string &name, const Rect &rect) {
    if(!spriteMapping[name]) {
        spriteMapping[name] = std::make_shared<Sprite>(texture, rect);
    }
}

void SpriteAtlas::mark(const std::string &name, const std::vector<Rect> &frames, bool loop, int framesPerSecond) {
    if(!spriteMapping[name]) {
        spriteMapping[name] = std::make_shared<Sprite>(texture, frames, loop, framesPerSecond);
    }
}

void SpriteAtlas::markGrid(const std::string &name, const Rect &first, int cols, int rows, bool loop, int framesPerSecond) {
    if(!spriteMapping[name]) {
       spriteMapping[name] = std::make_shared<Sprite>(texture, first, cols, rows, loop, framesPerSecond);
    }
}

void SpriteAtlas::unmark(const std::string &name) {
    if(spriteMapping[name]) {
        spriteMapping.erase(name);
    }
}

std::shared_ptr<Sprite> SpriteAtlas::get(const std::string &name) {
    return spriteMapping[name];
}
