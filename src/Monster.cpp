#include "Monster.h"
#include "actions/MoveAction.h"
#include "GameManager.h"

Monster::Monster(GameManager *gameManager, const Vector2D &position,
                 const SpriteAnimator &animator)
        : Entity(gameManager, position, animator), rng(dev()) {}

std::shared_ptr<Action> Monster::takeTurn() {
    Direction direction = Direction::NONE;
    std::vector<Direction> availableDirections;

//    auto isNotWall = [&](const Vector2D& relPos) {
//        Vector2D tilePos = getPosition() + relPos;
//        return gameManager->getMap()->isTileNone(tilePos.x, tilePos.y, { TileType::WALL });
//    };
//
//    auto isNotPositionTaken = [&](const Vector2D& relPos) {
//        Vector2D targetPos = getPosition() + relPos;
//        return isNotWall(relPos) && !gameManager->isPositionTaken(targetPos);
//    };

    std::vector<TileType> collidableTiles = { TileType::WALL };

    if(canMoveTo(Direction::RIGHT, collidableTiles)) {
        availableDirections.emplace_back(Direction::RIGHT);
    }
    if(canMoveTo(Direction::LEFT, collidableTiles)) {
        availableDirections.emplace_back(Direction::LEFT);
    }
    if(canMoveTo(Direction::UP, collidableTiles)) {
        availableDirections.emplace_back(Direction::UP);
    }
    if(canMoveTo(Direction::DOWN, collidableTiles)) {
        availableDirections.emplace_back(Direction::DOWN);
    }

    if(!availableDirections.empty()) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, availableDirections.size() - 1);
        int randomIndex = dist(rng);
        direction = availableDirections[randomIndex];
    }

    return std::make_shared<MoveAction>(this, direction, gameManager->getUnitSize());
}
