#include "MapBuilder.h"

MapBuilder::MapBuilder(int width, int height)
    : map(std::make_shared<Map>(width, height)) {}

MapBuilder& MapBuilder::fill(Sprite *tileSprite, int width, int height) {
    MapTile grass = {tileSprite, LightLevel::LIT, false};
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            map->put(j, i, grass);
        }
    }
    return *this;
}

std::shared_ptr<Map> MapBuilder::build() {
    std::shared_ptr<Map> toReturn = map;
    map = nullptr;
    return toReturn;
}
