#pragma once

#include <random>
#include "Entity.h"

class GameManager;

class Monster : public Entity {
    std::random_device dev;
    std::mt19937 rng;

public:
    Monster(GameManager *gameManager, const Vector2D &position, const SpriteAnimator &animator);
    std::shared_ptr<Action> takeTurn() override;
};
