#pragma once

#include "Action.h"
#include "../core/Vector2D.h"
#include "../core/SpriteAnimator.h"
#include "../Entity.h"
#include "Direction.h"

class MoveAction : public Action {
    Entity* entity;
    Direction direction;
    Vector2D targetPosition;
    bool interpolate;

    static Vector2D getTargetVector(const Direction& dir);
public:
    MoveAction(Entity *entity, const Direction &direction, int moveUnit, bool interpolate = true);
    ActionState perform() override;
};
