#pragma once

#include "Action.h"
#include "../core/Vector2D.h"
#include "../core/SpriteAnimator.h"
#include "../Entity.h"

enum class Direction {
    RIGHT, UP, LEFT, DOWN, NONE
};

class MoveAction : public Action {
    Entity* entity;
    Direction direction;
    Vector2D targetPosition;
    bool interpolate;

    // TODO: Move this UNIT constant elsewhere
    static const int UNIT = 16;

    static Vector2D getTargetVector(const Direction& dir);
public:
    MoveAction(Entity *entity, const Direction &direction, bool interpolate = true);
    ActionState perform() override;
};
