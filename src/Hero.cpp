#include "Hero.h"
#include "core/GameEngine.h"
#include "actions/MoveAction.h"


Hero::Hero(const Vector2D &position, const SpriteAnimator &animator)
    : Entity(position, animator), rng(dev()), randomInt(0, 4) {}

std::shared_ptr<Action> Hero::takeTurn() {
    auto randomDir = (Direction) randomInt(rng);
    return std::make_shared<MoveAction>(animator, position, randomDir);
}
