#include "PlayerInputAction.h"
#include "MoveAction.h"
#include "../Hero.h"

PlayerInputAction::PlayerInputAction(GameManager *gameManager, InputHandler& inputHandler)
    : gameManager(gameManager), inputHandler(inputHandler) {}

ActionState PlayerInputAction::perform() {
    Direction moveDir = Direction::NONE;
    Vector2D heroPos = gameManager->getHero()->getPosition();
    Vector2D relPos;

    if(inputHandler.is("right")) {
        moveDir = Direction::RIGHT;
        relPos = Vector2D{1, 0};
    }
    if(inputHandler.is("left")) {
        moveDir = Direction::LEFT;
        relPos = Vector2D{-1, 0};
    }
    if(inputHandler.is("up")) {
        moveDir = Direction::UP;
        relPos = Vector2D{0, -1};
    }
    if(inputHandler.is("down")) {
        moveDir = Direction::DOWN;
        relPos = Vector2D{0, 1};
    }

    Vector2D tilePos = heroPos / 16 + relPos;
    if(gameManager->getMap()->isTileAny(tilePos.x, tilePos.y, {TileType::WALL })
        || gameManager->isPositionTaken(heroPos + relPos * 16)) {
        moveDir = Direction::NONE;
    }

    if(moveDir != Direction::NONE) {
        chainAction = std::make_shared<MoveAction>(gameManager->getHero().get(), moveDir);
        return ActionState::DONE;
    }

    return ActionState::RUNNING;
}
