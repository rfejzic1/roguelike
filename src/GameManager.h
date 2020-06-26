#pragma once

#include <memory>
#include <vector>
#include "Map.h"
#include "core/GameEngine.h"
#include "core/SpriteAnimator.h"

class Entity;
class Hero;

class GameManager {
    GameEngine& gameEngine;
    std::vector<std::shared_ptr<Entity>> entities;
    std::shared_ptr<Hero> hero;
    std::shared_ptr<Map> map;
    const int UNIT;
public:
    explicit GameManager(GameEngine &gameEngine, const std::shared_ptr<Map> &map, int unitSize);
    std::shared_ptr<Map> getMap();
    std::vector<std::shared_ptr<Entity>>& getEntities();
    std::shared_ptr<Hero> getHero();
    void createHero(const Vector2D &position, const SpriteAnimator& animator);
    void createMonster(const Vector2D &position, const SpriteAnimator& animator);
    bool isPositionTaken(const Vector2D& position);
    int getUnitSize();
};
