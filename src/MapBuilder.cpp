#include "MapBuilder.h"

MapBuilder::MapBuilder(int width, int height)
    : map(std::make_shared<Map>(width, height)) {}

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
