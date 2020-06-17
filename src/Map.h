#pragma once

#include <memory>
#include "Matrix.h"

class Sprite;
class Renderer;

struct MapTile {
    std::shared_ptr<Sprite> sprite;
    bool collidable;

    MapTile(const std::shared_ptr<Sprite>& sprite, bool collidable)
        : sprite(sprite), collidable(collidable) {}
};

class Map {
    int width;
    int height;
    Matrix<std::shared_ptr<MapTile>> map;
public:
    Map(int mapWidth, int mapHeight);
    void put(int x, int y, const MapTile& tile);
    void remove(int x, int y);
    void render(Renderer* renderer);
    int getWidth() const;
    int getHeight() const;
};
