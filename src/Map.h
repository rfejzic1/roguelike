#pragma once

#include <vector>
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

typedef Matrix<std::shared_ptr<MapTile>> MapLayer;

class Map {
    int width;
    int height;
    int tileSize;
    std::vector<MapLayer> mapLayers;
    int currentLayer;

    MapLayer& getCurrentLayer();
public:
    Map(int mapWidth, int mapHeight, int tileSize);
    void addLayer();
    void put(int x, int y, const MapTile& tile);
    void remove(int x, int y);
    void render(Renderer* renderer);
    void renderLayer(Renderer* renderer, int layer);
    int getWidth() const;
    int getHeight() const;
};
