#pragma once

#include "Action.h"
#include "../core/Vector2D.h"
#include "../core/SpriteAnimator.h"

enum class Direction {
    RIGHT, UP, LEFT, DOWN, NONE
};

class MoveAction : public Action {
    SpriteAnimator& animator;
    Vector2D& position;
    Direction direction;
    Vector2D targetPosition;

    // TODO: Move this UNIT constant elsewhere
    static const int UNIT = 16;

    static Vector2D getTargetVector(const Direction& dir);
public:
    MoveAction(SpriteAnimator &animator, Vector2D &position, const Direction &direction);
    ActionState perform() override;
};
