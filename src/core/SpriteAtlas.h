#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Texture.h"
#include "Sprite.h"

typedef std::unordered_map<std::string, std::shared_ptr<Sprite>> SpriteMapping;

class SpriteAtlas {
    std::shared_ptr<Texture> texture;
    SpriteMapping spriteMapping;
public:
    explicit SpriteAtlas(std::shared_ptr<Texture> texture);
    void mark(const std::string& name, const Rect& rect);
    void mark(const std::string& name, const std::vector<Rect> &frames, bool loop, int framesPerSecond);
    void markGrid(const std::string &name, const Rect &first, int cols, int rows, bool loop, int framesPerSecond);
    void unmark(const std::string& name);
    std::shared_ptr<Sprite> get(const std::string& name);
};
