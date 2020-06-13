#include "Game.h"
#include "core/SpriteAnimator.h"

Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character_idle", "/home/rijad/Projects/roguelike/images/character_idle.png");
    engine.getTextureManager().load("character_walk", "/home/rijad/Projects/roguelike/images/character_walk.png");
    engine.getTextureManager().load("tileset", "/home/rijad/Projects/roguelike/images/tileset.png");
}

int Game::run() {
    std::shared_ptr<Texture> characterIdleTexture = engine.getTextureManager().get("character_idle");
    std::shared_ptr<Texture> characterWalkTexture = engine.getTextureManager().get("character_walk");
    std::shared_ptr<Texture> tilesetTexture = engine.getTextureManager().get("tileset");

    Sprite blacksmith_idle = Sprite(characterIdleTexture.get(), 4, 1, true, 15);
    Sprite blacksmith_walk = Sprite(characterWalkTexture.get(), 4, 1, true, 3);
    Sprite tree = Sprite(tilesetTexture.get(), { UNIT * 6, 0, UNIT, UNIT });
    Sprite grass = Sprite(tilesetTexture.get(), { UNIT * 6, UNIT * 1, UNIT, UNIT });

    SpriteAnimator animator("idle", blacksmith_idle);
    animator.createState("walking", blacksmith_walk);

    double x = 0, y = 0;
    int targetX = 0, targetY = 0;
    bool moving = false;
    bool facingLeft = false;

    engine.getInputHandler().on("right", [&targetX, &moving, &facingLeft]() {
        if(!moving) {
            targetX += 1;
            moving = true;
            facingLeft = false;
        }
    });
    engine.getInputHandler().on("left", [&targetX, &moving, &facingLeft]() {
        if(!moving) {
            targetX -= 1;
            moving = true;
            facingLeft = true;
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

    engine.loop([this, &x, &y, &targetX, &targetY, &moving, &animator, &tree, &grass, &facingLeft](double delta) {
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
                grass.render(&engine.getRenderer(), {UNIT * j, UNIT * i}, false);
            }
        }

        animator.setState(moving ? "walking" : "idle");

        tree.render(&engine.getRenderer(), {UNIT * 2, UNIT * 6});
        tree.render(&engine.getRenderer(), {UNIT * 6, UNIT * 4});
        animator.getSprite().render(&engine.getRenderer(), {(int) x, (int) y}, facingLeft);
    });

    return 0;
}
