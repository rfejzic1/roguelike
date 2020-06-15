#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <list>
#include <SDL2/SDL_events.h>

typedef std::unordered_map<std::string, SDL_KeyCode> InputMapping;
typedef std::function<void(void)> HandlerFunction;
typedef std::unordered_map<SDL_KeyCode, std::list<HandlerFunction>> Subscription;
typedef std::unordered_map<SDL_KeyCode, bool> InputState;

class InputHandler {
    InputMapping inputMapping;
    InputState inputState;
    Subscription keyDownSubscription;

    InputHandler();
    void initializeInputs();
public:
    bool pollInputs();
    void on(const std::string& input, const HandlerFunction& handlerFunction);
    bool is(const std::string& input);
    friend class GameEngine;
};
