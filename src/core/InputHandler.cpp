#include "InputHandler.h"

InputHandler::InputHandler() {
    initializeInputs();
}

void InputHandler::initializeInputs() {
    inputMapping["right"] = SDLK_RIGHT;
    inputMapping["left"] = SDLK_LEFT;
    inputMapping["up"] = SDLK_UP;
    inputMapping["down"] = SDLK_DOWN;
    inputMapping["action"] = SDLK_SPACE;
}

// TODO: Think of a better way to handle quit event!
bool InputHandler::pollInputs() {

    for(auto& it : inputState) {
        if(it.second == KeyState::PRESSED) {
            inputState[it.first] = KeyState::DOWN;
        }
    }

    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
        if(event.type == SDL_QUIT) {
            return false;
        }

        if(event.type == SDL_KEYDOWN) {
            auto keyCode = (SDL_KeyCode) event.key.keysym.sym;
            if(inputState[keyCode] == KeyState::UP) {
                inputState[keyCode] = KeyState::PRESSED;
            }
            for(HandlerFunction& function : keyDownSubscription[keyCode]) {
                function();
            }
        } else if(event.type == SDL_KEYUP) {
            auto keyCode = (SDL_KeyCode) event.key.keysym.sym;
            inputState[keyCode] = KeyState::UP;
        }
    }

    return true;
}

void InputHandler::on(const std::string &input, const HandlerFunction &handlerFunction) {
    SDL_KeyCode keyCode = inputMapping[input];
    keyDownSubscription[keyCode].emplace_back(handlerFunction);
}

bool InputHandler::is(const std::string &input) {
    SDL_KeyCode keyCode = inputMapping[input];
    KeyState keyState = inputState[keyCode];
    return keyState == KeyState::DOWN || keyState == KeyState::PRESSED;
}

bool InputHandler::isPressed(const std::string &input) {
    SDL_KeyCode keyCode = inputMapping[input];
    KeyState keyState = inputState[keyCode];
    return keyState == KeyState::PRESSED;
}
