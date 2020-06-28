#include "Monster.h"
#include "actions/MoveAction.h"
#include "GameManager.h"

Monster::Monster(GameManager *gameManager, const Vector2D &position,
                 const SpriteAnimator &animator)
        : Entity(gameManager, position, animator), rng(dev()) {}

std::shared_ptr<Action> Monster::takeTurn() {
    Direction direction;
    std::vector<Direction> availableDirections = { Direction::NONE };

    std::vector<TileType> collidableTiles = { TileType::WALL };

    auto dirs = { Direction::RIGHT, Direction::LEFT, Direction::UP, Direction::DOWN };

    for(auto& dir : dirs) {
        if(canMoveTo(dir, collidableTiles)) {
            availableDirections.emplace_back(dir);
        }
    }

    std::uniform_int_distribution<std::mt19937::result_type> dist(0, availableDirections.size() - 1);
    int randomIndex = dist(rng);
    direction = availableDirections[randomIndex];

    return std::make_shared<MoveAction>(this, direction, gameManager->getUnitSize(), interpolate);
}
