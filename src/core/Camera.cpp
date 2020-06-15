#include "Camera.h"
#include "Renderer.h"

Camera::Camera(const Vector2D &position)
    : position(position) {}

void Camera::move(const Vector2D &newPosition) {
    position = newPosition;
}

Vector2D Camera::getPosition() {
    return position;
}

void Camera::moveBy(const Vector2D &delta) {
    position += delta;
}

void Camera::snapFollowTarget(const Vector2D &targetPosition, int snapWidth, int snapHeight) {
    if(targetPosition.x >= getPosition().x + snapWidth) {
        moveBy({ snapWidth, 0 });
    }
    if(targetPosition.x < getPosition().x) {
        moveBy({ -snapWidth, 0 });
    }
    if(targetPosition.y < getPosition().y) {
        moveBy({ 0, -snapHeight });
    }
    if(targetPosition.y >= getPosition().y + snapHeight) {
        moveBy({ 0, snapHeight });
    }
}

void Camera::setRenderer(Renderer *newRenderer) {
    renderer = newRenderer;
}
