#include "Map.h"
#include "core/Renderer.h"
#include "core/Sprite.h"

Map::Map(int mapWidth, int mapHeight)
    : width(mapWidth), height(mapHeight), map(height, width, nullptr)
{

}

// Make a GameObject class and have it have an abstract "void render()" method
// Which derived classes can implement, like this Map class should
void Map::render(Renderer *renderer) {
    const int UNIT = 16;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            auto tile = map.get(i, j);
            if(tile) {
                tile->sprite->render(renderer, { j * UNIT, i * UNIT });
            }
        }
    }
}

void Map::put(int x, int y, const MapTile &tile) {
    map.set(y, x, std::make_shared<MapTile>(tile));
}

void Map::remove(int x, int y) {
    map.set(y, x, nullptr);
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
