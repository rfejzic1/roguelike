#pragma once

#include "core/GameEngine.h"

class Game {
    GameEngine engine;

    static const int UNIT = 16;
    static const int VIEW_HEIGHT = UNIT * 9;
    static const int VIEW_WIDTH = UNIT * 16;
    static const int SCALE = 2;

public:
    Game();
    int run();
};
