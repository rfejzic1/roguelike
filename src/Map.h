#pragma once

#include <memory>
#include "Matrix.h"

class Sprite;
class Renderer;

struct MapTile {
    Sprite* tileSprite; // TODO: Use integer IDs for tile sprites or use names?
    bool collidable;
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
};
