#include "Monster.h"
#include "actions/MoveAction.h"

Monster::Monster(const Vector2D &position, const SpriteAnimator &animator)
        : Entity(position, animator), rng(dev()), dist(0, 4) {}

std::shared_ptr<Action> Monster::takeTurn() {
    auto direction = (Direction) dist(rng);
    return std::make_shared<MoveAction>(this, direction);
}