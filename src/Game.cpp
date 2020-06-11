#include "Game.h"

Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character", "/home/rijad/Projects/roguelike/images/character.png");
}

Renderer &Game::getRenderer() {
    return engine.getRenderer();
}

int Game::run() {
    std::shared_ptr<Texture> character = engine.getTextureManager().get("character");

    int x = 0, y = 0;

    engine.getInputHandler().on("right", [&x]() {
        x += 1;
    });
    engine.getInputHandler().on("left", [&x]() {
        x -= 1;
    });
    engine.getInputHandler().on("up", [&y]() {
        y -= 1;
    });
    engine.getInputHandler().on("down", [&y]() {
        y += 1;
    });

    engine.loop([this, &x, &y, &character](double delta) {
        SDL_Log("fps: %lf", engine.getFPS());
        SDL_Rect charRect = { x * UNIT, y * UNIT, UNIT, UNIT };
        getRenderer().render(character.get(), nullptr, &charRect);
    });

    return 0;
}
