#include "GameManager.h"
#include "Hero.h"
#include "Monster.h"

GameManager::GameManager(GameEngine &gameEngine, const std::shared_ptr<Map> &map, int unitSize)
    : gameEngine(gameEngine), map(map), UNIT(unitSize) {}

std::shared_ptr<Map> GameManager::getMap() {
    return map;
}

std::vector<std::shared_ptr<Entity>>& GameManager::getEntities() {
    return entities;
}

void GameManager::createHero(const Vector2D &position, const SpriteAnimator &animator) {
    hero = std::make_shared<Hero>(gameEngine, this, position, animator);
    entities.emplace_back(hero);
}

void GameManager::createMonster(const Vector2D &position, const SpriteAnimator &animator) {
    entities.emplace_back(std::make_shared<Monster>(this, position, animator));
}

std::shared_ptr<Hero> GameManager::getHero() {
    return hero;
}

bool GameManager::isPositionTaken(const Vector2D &position) {
    for(auto& entity : entities) {
        if(entity->getPosition() == position) {
            return true;
        }
    }
    return false;
}

int GameManager::getUnitSize() {
    return UNIT;
}
