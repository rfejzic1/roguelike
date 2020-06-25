#include "MapBuilder.h"

MapBuilder::MapBuilder(int width, int height, int tileSize)
    : map(std::make_shared<Map>(width, height, tileSize)) {}

std::shared_ptr<Map> MapBuilder::build() {
    std::shared_ptr<Map> toReturn = map;
    map = nullptr;
    return toReturn;
}

MapBuilder & MapBuilder::fill(const std::shared_ptr<MapTile> &tile, int x, int y, int width, int height) {
    for(int i = y; i < y + height; i++) {
        for(int j = x; j < x + width; j++) {
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
