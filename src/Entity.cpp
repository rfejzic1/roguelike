#include "Entity.h"
#include "core/SpriteAnimator.h"
#include "core/GameEngine.h"

Entity::Entity(const Vector2D &position, const SpriteAnimator &animator)
    : position(position), animator(animator) {}

void Entity::render(Renderer *renderer) {
    animator.getSprite().render(renderer, position, facingLeft);
}

Vector2D Entity::getPosition() const {
    return position;
}
