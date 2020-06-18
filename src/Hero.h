#pragma once

#include "Entity.h"

class Hero : public Entity {
    GameEngine& engine;
public:
    Hero(GameEngine& gameEngine, const Vector2D &position, const SpriteAnimator &animator);
    std::shared_ptr<Action> takeTurn() override;
};
