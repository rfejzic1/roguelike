#include "TurnManager.h"

TurnManager::TurnManager() {}

TurnManager::TurnManager(const EntityCollection &entities)
    : entities(entities) {}

void TurnManager::update() {
    if(!currentAction) {
        currentAction = entities[currentEntityIndex]->takeTurn();
    }

    ActionState actionState = currentAction->perform();
    if(actionState == ActionState::DONE) {
        currentAction = currentAction->hasChainAction() ? currentAction->getChainAction() : nullptr;
        // If the current entity has no more chaining actions, process next entity...
        if(currentAction == nullptr) {
            currentEntityIndex = (currentEntityIndex + 1) % entities.size();
        }
    }
}

EntityCollection TurnManager::getEntities() {
    return entities;
}
