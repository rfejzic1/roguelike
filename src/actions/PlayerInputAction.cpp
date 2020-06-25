#include "PlayerInputAction.h"
#include "MoveAction.h"
#include "../Hero.h"
#include "../GameManager.h"

PlayerInputAction::PlayerInputAction(GameManager *gameManager, InputHandler& inputHandler)
    : gameManager(gameManager), inputHandler(inputHandler) {}

ActionState PlayerInputAction::perform() {
    Direction moveDir = Direction::NONE;
    Vector2D heroPos = gameManager->getHero()->getPosition() / 16;
    Vector2D checkPos = heroPos;

    if(inputHandler.is("right")) {
        moveDir = Direction::RIGHT;
        checkPos = heroPos + Vector2D{1, 0};
    }
    if(inputHandler.is("left")) {
        moveDir = Direction::LEFT;
        checkPos = heroPos + Vector2D{-1, 0};
    }
    if(inputHandler.is("up")) {
        moveDir = Direction::UP;
        checkPos = heroPos + Vector2D{0, -1};
    }
    if(inputHandler.is("down")) {
        moveDir = Direction::DOWN;
        checkPos = heroPos + Vector2D{0, 1};
    }

    if(gameManager->getMap()->isTileAny(checkPos.x, checkPos.y, { TileType::WALL })) {
        moveDir = Direction::NONE;
    }

    if(moveDir != Direction::NONE) {
        chainAction = std::make_shared<MoveAction>(gameManager->getHero().get(), moveDir);
        return ActionState::DONE;
    }

    return ActionState::RUNNING;
}
