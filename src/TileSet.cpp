#include "TileSet.h"

TileSet::TileSet(SpriteAtlas &spriteAtlas)
    : spriteAtlas(spriteAtlas) {}

void TileSet::put(const std::string &tileName, const std::string &spriteName, const TileType &tileType) {
    if(!tileMapping[tileName]) {
        tileMapping[tileName] = std::make_shared<MapTile>(spriteAtlas.get(spriteName), tileType);
    }
}

void TileSet::remove(const std::string &name) {
    tileMapping.erase(name);
}

std::shared_ptr<MapTile> TileSet::get(const std::string &name) {
    return tileMapping[name];
}
