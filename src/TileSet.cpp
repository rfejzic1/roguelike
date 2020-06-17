#include "TileSet.h"

TileSet::TileSet(SpriteAtlas &spriteAtlas)
    : spriteAtlas(spriteAtlas) {}

void TileSet::put(const std::string &tileName, const std::string &spriteName, bool isCollidable) {
    if(!tileMapping[tileName]) {
        tileMapping[tileName] = std::make_shared<MapTile>(spriteAtlas.get(spriteName), isCollidable);
    }
}

void TileSet::remove(const std::string &name) {
    tileMapping.erase(name);
}

std::shared_ptr<MapTile> TileSet::get(const std::string &name) {
    return tileMapping[name];
}
