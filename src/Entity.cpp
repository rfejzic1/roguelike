#include "Entity.h"
#include "core/SpriteAnimator.h"
#include "core/GameEngine.h"
#include "GameManager.h"

Entity::Entity(GameManager *gameManager, const Vector2D &position, const SpriteAnimator &animator)
    : gameManager(gameManager), position(position * gameManager->getUnitSize()), animator(animator),
      interpolate(true) {}

void Entity::render(Renderer *renderer) {
    animator.getSprite().render(renderer, position, facingLeft);
}

SpriteAnimator &Entity::getSpriteAnimator() {
    return animator;
}

void Entity::setFacingLeft(bool left) {
    facingLeft = left;
}

Vector2D Entity::getPosition() {
    return position / gameManager->getUnitSize();
}

void Entity::setPosition(const Vector2D &newPosition) {
    position = newPosition * gameManager->getUnitSize();
}

Vector2D &Entity::getTruePosition() {
    return position;
}

bool Entity::canMoveTo(Direction direction, const std::vector<TileType> &tileTypes) {
    Vector2D targetPos;

    switch (direction) {
        case Direction::RIGHT:
            targetPos = {1, 0};
            break;
        case Direction::UP:
            targetPos = {0, -1};
            break;
        case Direction::LEFT:
            targetPos = {-1, 0};
            break;
        case Direction::DOWN:
            targetPos = {0, 1};
            break;
        default:
            targetPos = {0, 0};
    }

    targetPos = targetPos + getPosition();

    return !gameManager->getMap()->isTileAny(targetPos.x, targetPos.y, {TileType::WALL })
            && !gameManager->isPositionTaken(targetPos);
}

void Entity::setInterpolate(bool doInterpolate) {
    interpolate = doInterpolate;
}
