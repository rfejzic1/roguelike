#include "Hero.h"
#include "core/GameEngine.h"
#include "actions/PlayerInputAction.h"
#include "GameManager.h"


Hero::Hero(GameEngine &gameEngine, GameManager *gameManager, const Vector2D &position, const SpriteAnimator &animator)
    : Entity(gameManager, position, animator), engine(gameEngine) {}

std::shared_ptr<Action> Hero::takeTurn() {
    return std::make_shared<PlayerInputAction>(gameManager, engine.getInputHandler());
}
