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

    //Initialize SDL_ttf
    if(TTF_Init() == -1) {
        SDL_Log( "Error: %s", TTF_GetError());
        return;
    }

    //Open the font
    font = TTF_OpenFont( "./fonts/PressStart2P-Regular.ttf", 8);
    if(!font) {
        SDL_Log( "Error: %s", TTF_GetError());
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
    renderer->setGameEngine(this);
    inputHandler = new InputHandler();
    textureManager = new TextureManager(renderer->getSDLRenderer());
}

GameEngine::~GameEngine() {
    if(window) {
        delete renderer;
        delete inputHandler;
        delete textureManager;
        TTF_CloseFont(font);
        font = nullptr;
        textureManager = nullptr;
        inputHandler = nullptr;
        renderer = nullptr;
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    TTF_Quit();
    IMG_Quit();
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
            delta = deltaTicks;
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

TTF_Font *GameEngine::getFont() {
    return font;
}
