#pragma once

#include <memory>
#include "Matrix.h"

class Sprite;
class Renderer;

enum class LightLevel {
    UNLIT, DARK, LIT, EMISSIVE
};

struct MapTile {
    Sprite* tileSprite; // TODO: Use integer IDs for tile sprites or use names?
    LightLevel lightLevel;
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
