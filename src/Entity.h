#pragma once

#include "core/Vector2D.h"
#include "core/Renderable.h"
#include "core/SpriteAnimator.h"

class Entity : public Renderable {
    Vector2D position;
    SpriteAnimator animator;
    bool facingLeft = false;
public:
    explicit Entity(const Vector2D &position, const SpriteAnimator &animator);
    void render(Renderer *renderer) override;
    virtual ~Entity() = default;
};
