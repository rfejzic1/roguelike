#pragma once

#include "core/Vector2D.h"
#include "core/Renderable.h"
#include "core/SpriteAnimator.h"
#include "actions/Action.h"
#include "actions/Direction.h"
#include "Map.h"

class GameEngine;
class GameManager;

class Entity : public Renderable {
protected:
    GameManager* gameManager;
private:
    Vector2D position;
protected:
    SpriteAnimator animator;
    bool facingLeft = false;
public:
    Entity(GameManager *gameManager, const Vector2D &position, const SpriteAnimator &animator);
    void render(Renderer *renderer) override;
    virtual std::shared_ptr<Action> takeTurn() = 0;
    Vector2D& getTruePosition();
    Vector2D getPosition();
    void setPosition(const Vector2D& position);
    SpriteAnimator& getSpriteAnimator();
    void setFacingLeft(bool left);
    bool canMoveTo(Direction direction, const std::vector<TileType>& tileTypes);
    ~Entity() override = default;
};
