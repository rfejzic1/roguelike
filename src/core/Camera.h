#pragma once

#include "Vector2D.h"

class Camera {
    Vector2D position;
public:
    Camera() = default;
    explicit Camera(const Vector2D& position);
    void move(const Vector2D& newPosition);
    void moveBy(const Vector2D& delta);
    Vector2D getPosition();
};
