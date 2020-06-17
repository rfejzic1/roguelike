#include "MapBuilder.h"

MapBuilder::MapBuilder(int width, int height, int tileSize)
    : map(std::make_shared<Map>(width, height, tileSize)) {}

std::shared_ptr<Map> MapBuilder::build() {
    std::shared_ptr<Map> toReturn = map;
    map = nullptr;
    return toReturn;
}

MapBuilder& MapBuilder::fill(const std::shared_ptr<MapTile> &tile, int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            map->put(j, i, *tile);
        }
    }
    return *this;
}

MapBuilder &MapBuilder::put(const std::shared_ptr<MapTile> &tile, const Vector2D &position) {
    map->put(position.x, position.y, *tile);
    return *this;
}

MapBuilder &MapBuilder::addLayer() {
    map->addLayer();
    return *this;
}
