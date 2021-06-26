#pragma once

#include <string>
#include <unordered_map>
#include "Sprite.h"

class SpriteAnimator {
    std::unordered_map<std::string, Sprite> states;
    std::string currentState;
public:
    SpriteAnimator(const std::string& initialState, const Sprite& sprite);
    void createState(const std::string& state, const Sprite& sprite);
    void deleteState(const std::string& state);
    void setState(const std::string& state);
    Sprite& getSprite();
};
