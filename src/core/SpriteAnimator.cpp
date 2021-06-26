#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator(const std::string &initialState, const Sprite &sprite) {
    createState(initialState, sprite);
    currentState = initialState;
}

void SpriteAnimator::createState(const std::string &state, const Sprite &sprite) {
    states[state] = sprite;
}

void SpriteAnimator::deleteState(const std::string &state) {
    states.erase(state);
}

void SpriteAnimator::setState(const std::string &state) {
    if(state != currentState && states.find(state) != states.end()) {
        states[state].reset();
        currentState = state;
    }
}

Sprite &SpriteAnimator::getSprite() {
    return states[currentState];
}
