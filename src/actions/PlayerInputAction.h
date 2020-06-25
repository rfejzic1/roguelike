#pragma once

#include "Action.h"
#include "../core/InputHandler.h"

class GameManager;

class PlayerInputAction : public Action {
    GameManager* gameManager;
    InputHandler& inputHandler;
public:
    explicit PlayerInputAction(GameManager *gameManager, InputHandler& inputHandler);
    ActionState perform() override;
};
