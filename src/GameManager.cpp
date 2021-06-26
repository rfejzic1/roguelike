#include "GameManager.h"
#include "Hero.h"
#include "Monster.h"

GameManager::GameManager(GameEngine &gameEngine, const std::shared_ptr<Map> &map, int unitSize)
    : gameEngine(gameEngine), map(map), mapObjects(map->getHeight(), map->getWidth()), UNIT(unitSize) {}

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
    auto mapObject = getMapObjectAt(position);
    if(mapObject && mapObject->isCollidable()) {
        return true;
    }

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

std::shared_ptr<MapObject> GameManager::getMapObjectAt(const Vector2D& position) {
    return mapObjects.get(position.y, position.x);
}

void GameManager::createMapObject(const Vector2D &position, const std::shared_ptr<Sprite> &sprite, bool isCollidable) {
    auto mapObject = std::make_shared<MapObject>(position * UNIT, sprite, isCollidable);
    mapObjects.set(position.y, position.x, mapObject);
}

void GameManager::render() {
    auto renderer = &gameEngine.getRenderer();
    getMap()->render(renderer);

    for(int i = 0; i < getMap()->getHeight(); i++) {
        for(int j = 0; j < getMap()->getWidth(); j++) {
            auto mapObject = getMapObjectAt({j, i});
            if(mapObject) {
                mapObject->render(renderer);
            }
        }
    }

    for(auto& entity : getEntities()) {
        Vector2D pos = entity->getTruePosition();
        bool isEntityInView = renderer->getCamera().isInView({ pos.x, pos.y, UNIT, UNIT });
        entity->setInterpolate(isEntityInView);
        entity->render(renderer);
    }
}
