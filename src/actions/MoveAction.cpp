#include "MoveAction.h"

MoveAction::MoveAction(Entity *entity, const Direction &direction, int moveUnit, bool interpolate)
    : entity(entity), direction(direction), interpolate(interpolate),
      targetPosition(entity->getTruePosition() + getTargetVector(direction) * moveUnit)
{
    entity->getSpriteAnimator().setState("walk");
}

ActionState MoveAction::perform() {
    int step = 1;
    int targetX = targetPosition.x;
    int targetY = targetPosition.y;

    Vector2D& position = entity->getTruePosition();

    if(interpolate) {
        if(position.x < targetX) {
            position.x += step;
            entity->setFacingLeft(false);
        }
        if(position.x > targetX) {
            position.x -= step;
            entity->setFacingLeft(true);
        }
        if(position.y < targetY) {
            position.y += step;
        }
        if(position.y > targetY) {
            position.y -= step;
        }
    } else {
        if(position.x < targetX) {
            entity->setFacingLeft(false);
        }
        if(position.x > targetX) {
            entity->setFacingLeft(true);
        }

        position.x = targetX;
        position.y = targetY;
    }

    if(position.x == targetX && position.y == targetY) {
        entity->getSpriteAnimator().setState("idle");
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
