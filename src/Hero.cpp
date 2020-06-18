#include "Hero.h"
#include "core/GameEngine.h"
#include "actions/PlayerInputAction.h"


Hero::Hero(GameEngine& gameEngine, const Vector2D &position, const SpriteAnimator &animator)
    : Entity(position, animator), engine(gameEngine) {}

std::shared_ptr<Action> Hero::takeTurn() {
    return std::make_shared<PlayerInputAction>(this, engine.getInputHandler());
}
