#include "PlayerInputAction.h"
#include "MoveAction.h"
#include "../Hero.h"

PlayerInputAction::PlayerInputAction(Hero *hero, InputHandler& inputHandler)
    : hero(hero), inputHandler(inputHandler) {}

ActionState PlayerInputAction::perform() {
    Direction moveDir = Direction::NONE;

    if(inputHandler.is("right")) {
        moveDir = Direction::RIGHT;
    }
    if(inputHandler.is("left")) {
        moveDir = Direction::LEFT;
    }
    if(inputHandler.is("up")) {
        moveDir = Direction::UP;
    }
    if(inputHandler.is("down")) {
        moveDir = Direction::DOWN;
    }

    if(moveDir != Direction::NONE) {
        chainAction = std::make_shared<MoveAction>(hero->animator, hero->position, moveDir);
        return ActionState::DONE;
    }

    return ActionState::RUNNING;
}
