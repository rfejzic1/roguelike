#include "TurnManager.h"

TurnManager::TurnManager(const EntityCollection &entities)
    : entities(entities)
{
    next();
}

void TurnManager::update() {
    if(hasAction()) {
        ActionState actionState = currentAction->perform();
        if(actionState == ActionState::DONE) {
            currentAction = currentAction->hasChainAction() ? currentAction->getChainAction() : nullptr;
        }
    }
}

EntityCollection TurnManager::getEntities() {
    return entities;
}

void TurnManager::next() {
    if(!hasAction()) {
        currentEntityIndex = (currentEntityIndex + 1) % entities.size();
        currentAction = entities[currentEntityIndex]->takeTurn();
    }
}

bool TurnManager::hasAction() {
    return currentAction != nullptr;
}

std::shared_ptr<Entity> TurnManager::getCurrentEntity() {
    return entities[currentEntityIndex];
}
