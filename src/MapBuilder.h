#pragma once

#include <memory>
#include "Map.h"

class MapBuilder {
    std::shared_ptr<Map> map;
public:
    MapBuilder(int width, int height);
    MapBuilder& fill(Sprite* tileSprite, int width, int height);
    std::shared_ptr<Map> build();
};
