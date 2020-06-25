#include "Monster.h"
#include "actions/MoveAction.h"
#include "GameManager.h"

Monster::Monster(GameManager *gameManager, const Vector2D &position,
                 const SpriteAnimator &animator)
        : Entity(gameManager, position, animator), rng(dev()) {}

std::shared_ptr<Action> Monster::takeTurn() {
    Direction direction = Direction::NONE;
    std::vector<Direction> availableDirections;

    // Bad: Relies on the order of enum elements in Direction
    Vector2D positions[4] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
    for(int i = 0; i < 4; i++) {
        Vector2D tilePos = position / 16 + positions[i];
        if(!gameManager->getMap()->isTileAny(tilePos.x, tilePos.y, {TileType::WALL })) {
            availableDirections.emplace_back((Direction) i);
        }
    }

    if(!availableDirections.empty()) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, availableDirections.size());
        int randomIndex = dist(rng);
        direction = availableDirections[randomIndex];
    }

    return std::make_shared<MoveAction>(this, direction);
}
