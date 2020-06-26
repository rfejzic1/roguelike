#include "Entity.h"
#include "core/SpriteAnimator.h"
#include "core/GameEngine.h"
#include "GameManager.h"

Entity::Entity(GameManager *gameManager, const Vector2D &position, const SpriteAnimator &animator)
    : gameManager(gameManager), position(position * gameManager->getUnitSize()), animator(animator) {}

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
