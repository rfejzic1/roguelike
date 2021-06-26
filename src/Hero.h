#pragma once

#include "Entity.h"
#include "GameManager.h"

class Hero : public Entity {
    GameEngine& engine;
public:
    Hero(GameEngine &gameEngine, GameManager *gameManager, const Vector2D &position, const SpriteAnimator &animator);
    std::shared_ptr<Action> takeTurn() override;
};
