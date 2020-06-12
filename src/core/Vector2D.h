#pragma once

struct Vector2D {
    int x = 0;
    int y = 0;

    Vector2D() = default;
    Vector2D(int x, int y) : x(x), y(y) {}
};