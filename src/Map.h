#pragma once

#include <vector>
#include <memory>
#include "Matrix.h"
#include "core/Renderable.h"

class Sprite;
class Renderer;

enum class TileType {
    GROUND, WALL
};

struct MapTile {
    std::shared_ptr<Sprite> sprite;
    TileType tileType;

    MapTile(const std::shared_ptr<Sprite>& sprite, const TileType& tileType)
        : sprite(sprite), tileType(tileType) {}
};

typedef Matrix<std::shared_ptr<MapTile>> MapLayer;

class Map : public Renderable {
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
    MapTile& getTile(int x, int y);
    bool isTileAny(int x, int y, const std::vector<TileType>& tileTypes);
    bool isTileNone(int x, int y, const std::vector<TileType>& tileTypes);
    void render(Renderer* renderer) override;
    void renderLayer(Renderer* renderer, int layer);
    int getWidth() const;
    int getHeight() const;
};
