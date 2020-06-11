#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include "InputHandler.h"
#include "TextureManager.h"

class GameEngine {
    bool isRunning = true;
    double avgFPS = 0;

    SDL_Window* window = nullptr;
    Renderer* renderer = nullptr;
    InputHandler* inputHandler = nullptr;
    TextureManager* textureManager = nullptr;

    static const int SCREEN_FPS = 120;
    static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

public:
    GameEngine(int width, int height, int scale = 1);
    void loop(const std::function<void(double)>& loopFunction);
    Renderer& getRenderer();
    InputHandler& getInputHandler();
    TextureManager& getTextureManager();
    double getFPS() const;
    ~GameEngine();
};
