#pragma once

#include "core/Vector2D.h"
#include "core/Renderable.h"
#include "core/SpriteAnimator.h"
#include "actions/Action.h"

class GameEngine;

class Entity : public Renderable {
protected:
    Vector2D position;
    SpriteAnimator animator;
    bool facingLeft = false;
public:
    Entity(const Vector2D &position, const SpriteAnimator &animator);
    void render(Renderer *renderer) override;
    virtual std::shared_ptr<Action> takeTurn() = 0;
    Vector2D getPosition() const;
    ~Entity() override = default;
};
