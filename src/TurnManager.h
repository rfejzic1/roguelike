#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityCollection;

class TurnManager {
    EntityCollection entities;
    unsigned int currentEntityIndex = 0;
    std::shared_ptr<Action> currentAction = nullptr;

public:
    TurnManager();
    explicit TurnManager(const EntityCollection& entities);
    void update();
    EntityCollection getEntities();
};
