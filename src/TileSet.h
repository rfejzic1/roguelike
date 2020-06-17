#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "Map.h"
#include "core/SpriteAtlas.h"

typedef std::unordered_map<std::string, std::shared_ptr<MapTile>> TileMapping;

class TileSet {
    TileMapping tileMapping;
    SpriteAtlas& spriteAtlas;
public:
    TileSet(SpriteAtlas& spriteAtlas);
    void put(const std::string &tileName, const std::string &spriteName, bool isCollidable);
    void remove(const std::string& name);
    std::shared_ptr<MapTile> get(const std::string& name);
};
