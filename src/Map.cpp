#include "Map.h"
#include "core/Renderer.h"
#include "core/Sprite.h"

Map::Map(int mapWidth, int mapHeight)
    : width(mapWidth), height(mapHeight)
{
    addLayer();
    currentLayer = 0;
}

void Map::addLayer() {
    mapLayers.emplace_back(height, width, nullptr);
    currentLayer += 1;
}

void Map::renderLayer(Renderer* renderer, int layer) {
    const int UNIT = 16;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            auto tile = mapLayers[layer].get(i, j);
            if(tile) {
                tile->sprite->render(renderer, { j * UNIT, i * UNIT });
            }
        }
    }
}

// Make a GameObject class and have it have an abstract "void render()" method
// Which derived classes can implement, like this Map class should
void Map::render(Renderer *renderer) {
    for(int i = 0; i < mapLayers.size(); i++) {
        renderLayer(renderer, i);
    }
}

void Map::put(int x, int y, const MapTile &tile) {
    getCurrentLayer().set(y, x, std::make_shared<MapTile>(tile));
}

void Map::remove(int x, int y) {
    getCurrentLayer().set(y, x, nullptr);
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

MapLayer &Map::getCurrentLayer() {
    return mapLayers[currentLayer];
}
