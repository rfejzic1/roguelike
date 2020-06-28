#include "MapObject.h"

#include <utility>

MapObject::MapObject(const Vector2D &position, std::shared_ptr<Sprite> sprite, bool isCollidable)
    : position(position), sprite(std::move(sprite)), collidable(isCollidable) {}

bool MapObject::isCollidable() const {
    return collidable;
}

void MapObject::render(Renderer *renderer) {
    sprite->render(renderer, position);
}
