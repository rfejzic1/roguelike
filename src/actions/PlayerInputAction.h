#pragma once

#include "Action.h"
#include "../core/InputHandler.h"

class Hero;

class PlayerInputAction : public Action {
    Hero* hero;
    InputHandler& inputHandler;
public:
    explicit PlayerInputAction(Hero* hero, InputHandler& inputHandler);
    ActionState perform() override;
};
