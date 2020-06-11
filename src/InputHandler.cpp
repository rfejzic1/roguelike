#include "InputHandler.h"

InputHandler::InputHandler() {
    initializeInputs();
}

void InputHandler::initializeInputs() {
    inputMapping["right"] = SDLK_RIGHT;
    inputMapping["left"] = SDLK_LEFT;
    inputMapping["up"] = SDLK_UP;
    inputMapping["down"] = SDLK_DOWN;
}

// TODO: Think of a better way to handle quit event!
bool InputHandler::pollInputs() {
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
        if(event.type == SDL_QUIT) {
            return false;
        }

        if(event.type == SDL_KEYDOWN) {
            auto keyCode = (SDL_KeyCode) event.key.keysym.sym;
            for(HandlerFunction& function : keyDownSubscription[keyCode]) {
                function();
            }
        }
    }

    return true;
}

void InputHandler::on(const std::string &input, const HandlerFunction &handlerFunction) {
    SDL_KeyCode keyCode = inputMapping[input];
    keyDownSubscription[keyCode].emplace_back(handlerFunction);
}
