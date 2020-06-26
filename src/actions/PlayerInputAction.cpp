#include "PlayerInputAction.h"
#include "MoveAction.h"
#include "../Hero.h"

PlayerInputAction::PlayerInputAction(GameManager *gameManager, InputHandler& inputHandler)
    : gameManager(gameManager), inputHandler(inputHandler) {}

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

    if(!gameManager->getHero()->canMoveTo(moveDir, { TileType::WALL })) {
        moveDir = Direction::NONE;
    }

    if(moveDir != Direction::NONE) {
        chainAction = std::make_shared<MoveAction>(gameManager->getHero().get(), moveDir, gameManager->getUnitSize());
        return ActionState::DONE;
    }

    return ActionState::RUNNING;
}
