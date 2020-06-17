#include "MoveAction.h"

MoveAction::MoveAction(SpriteAnimator& animator, Vector2D& position, const Direction& direction)
    : animator(animator), position(position), direction(direction),
      targetPosition(position + getTargetVector(direction) * UNIT)
{
    animator.setState("walk");
}

ActionState MoveAction::perform() {
    int step = 1;
    int targetX = targetPosition.x;
    int targetY = targetPosition.y;

    if(position.x < targetX) {
        position.x += step;
    }
    if(position.x > targetX) {
        position.x -= step;
    }
    if(position.y < targetY) {
        position.y += step;
    }
    if(position.y > targetY) {
        position.y -= step;
    }

    if(position.x == targetX && position.y == targetY) {
        animator.setState("idle");
        result = std::make_shared<ActionResult>(ActionResult::GOOD);
        return ActionState::DONE;
    }

    return ActionState::RUNNING;
}

Vector2D MoveAction::getTargetVector(const Direction& dir) {
    switch (dir) {
        case Direction::RIGHT:
            return {1, 0};
        case Direction::UP:
            return {0, -1};
        case Direction::LEFT:
            return {-1, 0};
        case Direction::DOWN:
            return {0, 1};
        default:
            return {0, 0};
    }
}
