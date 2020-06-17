#pragma once

#include <memory>
#include "Map.h"
#include "core/Vector2D.h"

class MapBuilder {
    std::shared_ptr<Map> map;
public:
    MapBuilder(int width, int height, int tileSize);
    MapBuilder& addLayer();
    MapBuilder& fill(const std::shared_ptr<MapTile> &tile, int width, int height);
    MapBuilder& put(const std::shared_ptr<MapTile> &tile, const Vector2D& position);
    std::shared_ptr<Map> build();
};
