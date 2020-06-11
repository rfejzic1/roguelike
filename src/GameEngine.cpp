#include "GameEngine.h"
#include "Timer.h"

GameEngine::GameEngine(int width, int height, int scale) {
    if(!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO)) {
        SDL_Init(SDL_INIT_VIDEO);
    }

    // Initialize image loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Log( "Error: %s", IMG_GetError());
        return;
    }

    window = SDL_CreateWindow(
            "roguelike",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width * scale,
            height * scale,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = new Renderer(window, width, height, scale);
    inputHandler = new InputHandler();
    textureManager = new TextureManager(*this);
}

GameEngine::~GameEngine() {
    if(window) {
        delete renderer;
        delete inputHandler;
        delete textureManager;
        textureManager = nullptr;
        inputHandler = nullptr;
        renderer = nullptr;
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

Renderer& GameEngine::getRenderer() {
    return *renderer;
}

InputHandler &GameEngine::getInputHandler() {
    return *inputHandler;
}

void GameEngine::loop(const std::function<void(double)>& loopFunction) {
    double delta = 0;
    unsigned int countedFrames = 0;
    Timer capTimer;
    Timer fpsTimer;

    fpsTimer.start();

    while(isRunning) {
        capTimer.start();

        isRunning = getInputHandler().pollInputs();

        getRenderer().clear();

        try {
            loopFunction(delta);
        } catch (std::exception& e) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Exception: %s", e.what());
        }

        getRenderer().update();

        // Calculate and correct fps
        avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.0 );
        if( avgFPS > 2000000 ) {
            avgFPS = 0;
        }

        countedFrames += 1;

        // If frame finished early
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICKS_PER_FRAME ) {
            // Wait remaining time
            int deltaTicks = SCREEN_TICKS_PER_FRAME - frameTicks;
            delta = deltaTicks / 1000.0;
            SDL_Delay(deltaTicks);
        }
    }
}

TextureManager &GameEngine::getTextureManager() {
    return *textureManager;
}

double GameEngine::getFPS() const {
    return avgFPS;
}
