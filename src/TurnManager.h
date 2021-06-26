#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

class TurnManager {
    std::vector<std::shared_ptr<Entity>>& entities;
    unsigned int currentEntityIndex = -1;
    std::shared_ptr<Action> currentAction = nullptr;

public:
    explicit TurnManager(std::vector<std::shared_ptr<Entity>>& entities);
    void update();
    bool hasAction();
    void next();
    std::shared_ptr<Entity> getCurrentEntity();
};
