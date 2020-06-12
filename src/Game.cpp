#include "Game.h"

Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character", "/home/rijad/Projects/roguelike/images/character.png");
    engine.getTextureManager().load("tileset", "/home/rijad/Projects/roguelike/images/tileset.png");
}

int Game::run() {
    std::shared_ptr<Texture> characterTexture = engine.getTextureManager().get("character");
    std::shared_ptr<Texture> tilesetTexture = engine.getTextureManager().get("tileset");

    Sprite blacksmith = Sprite(characterTexture.get(), 4, 1, 15);
    Sprite tree = Sprite(tilesetTexture.get(), { UNIT * 6, 0, UNIT, UNIT });
    Sprite grass = Sprite(tilesetTexture.get(), { UNIT * 6, UNIT * 1, UNIT, UNIT });

    double x = 0, y = 0;
    int targetX = 0, targetY = 0;
    bool moving = false;

    engine.getInputHandler().on("right", [&targetX, &moving]() {
        if(!moving) {
            targetX += 1;
            moving = true;
        }
    });
    engine.getInputHandler().on("left", [&targetX, &moving]() {
        if(!moving) {
            targetX -= 1;
            moving = true;
        }
    });
    engine.getInputHandler().on("up", [&targetY, &moving]() {
        if(!moving) {
            targetY -= 1;
            moving = true;
        }
    });
    engine.getInputHandler().on("down", [&targetY, &moving]() {
        if(!moving) {
            targetY += 1;
            moving = true;
        }
    });

    engine.loop([this, &x, &y, &targetX, &targetY, &moving, &blacksmith, &tree, &grass](double delta) {
        SDL_Log("fps: %lf", engine.getFPS());
        double step = 1;

        if(x < targetX * UNIT) {
            x += step;
        }
        if(x > targetX * UNIT) {
            x -= step;
        }
        if(y < targetY * UNIT) {
            y += step;
        }
        if(y > targetY * UNIT) {
            y -= step;
        }
        if(x == targetX * UNIT && y == targetY * UNIT) {
            moving = false;
        }

        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 16; j++) {
                grass.render(&engine.getRenderer(), { UNIT * j, UNIT * i });
            }
        }

        tree.render(&engine.getRenderer(), { UNIT * 2, UNIT * 6});
        tree.render(&engine.getRenderer(), { UNIT * 6, UNIT * 4});
        blacksmith.render(&engine.getRenderer(), { (int) x, (int) y });
    });

    return 0;
}
