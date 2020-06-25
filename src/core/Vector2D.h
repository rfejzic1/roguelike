#pragma once

struct Vector2D {
    int x = 0;
    int y = 0;

    Vector2D() = default;
    Vector2D(int x, int y) : x(x), y(y) {}

    Vector2D& operator +=(const Vector2D& other) {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2D& operator -=(const Vector2D& other) {
        *this += (-other);
        return *this;
    }

    Vector2D operator +(const Vector2D& other) const {
        return {
            x + other.x,
            y + other.y
        };
    }

    Vector2D operator -() const {
        return { -x, -y };
    }

    Vector2D operator -(const Vector2D& other) const {
        return *this + (-other);
    }

    Vector2D operator *(int value) const {
        return { this->x * value, this->y * value };
    }

    Vector2D operator /(int value) const {
        return { this->x / value, this->y / value };
    }

    bool operator ==(const Vector2D& other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool operator !=(const Vector2D& other) const {
        return !(*this == other);
    }

};