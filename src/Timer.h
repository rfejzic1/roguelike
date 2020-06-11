#pragma once

#include <SDL2/SDL_stdinc.h>

class Timer {
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool paused;
    bool started;
public:
    Timer();
    void start();
    void stop();
    void pause();
    void resume();
    Uint32 getTicks();
    bool isStarted();
    bool isPaused();
};
