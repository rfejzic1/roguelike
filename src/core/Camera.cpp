#include "Camera.h"

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
