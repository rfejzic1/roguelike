#pragma once

#include "Vector2D.h"

class Renderer;

class Camera {
    Vector2D position;
    Renderer* renderer = nullptr;

    void setRenderer(Renderer* newRenderer);
public:
    Camera() = default;
    explicit Camera(const Vector2D& position);
    void move(const Vector2D& newPosition);
    void moveBy(const Vector2D& delta);
    void snapFollowTarget(const Vector2D &targetPosition, int snapWidth, int snapHeight);
    Vector2D getPosition();
};
