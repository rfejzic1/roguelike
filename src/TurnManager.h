#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityCollection;

class TurnManager {
    EntityCollection entities;
    unsigned int currentEntityIndex = -1;
    std::shared_ptr<Action> currentAction = nullptr;

public:
    TurnManager() = default;
    explicit TurnManager(const EntityCollection& entities);
    void update();
    bool hasAction();
    void next();
    std::shared_ptr<Entity> getCurrentEntity();
    EntityCollection getEntities();
};
