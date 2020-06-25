#pragma once

#include "core/Vector2D.h"
#include "core/Renderable.h"
#include "core/SpriteAnimator.h"
#include "actions/Action.h"

class GameEngine;
class GameManager;

class Entity : public Renderable {
protected:
    GameManager* gameManager;
    Vector2D position;
    SpriteAnimator animator;
    bool facingLeft = false;
public:
    Entity(GameManager *gameManager, const Vector2D &position, const SpriteAnimator &animator);
    void render(Renderer *renderer) override;
    virtual std::shared_ptr<Action> takeTurn() = 0;
    Vector2D& getPosition();
    SpriteAnimator& getSpriteAnimator();
    void setFacingLeft(bool left);
    ~Entity() override = default;
};
