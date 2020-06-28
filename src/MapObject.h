#pragma once

#include <memory>
#include "core/Sprite.h"
#include "core/Renderable.h"

class MapObject : public Renderable {
    Vector2D position;
    std::shared_ptr<Sprite> sprite;
    bool collidable;
public:
    MapObject(const Vector2D &position, std::shared_ptr<Sprite> sprite, bool isCollidable);
    bool isCollidable() const;
    void render(Renderer *renderer) override;
};
