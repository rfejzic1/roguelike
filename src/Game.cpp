#include "Game.h"
#include "core/SpriteAnimator.h"
#include "MapBuilder.h"

Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character_idle", "/home/rijad/Projects/roguelike/images/character_idle.png");
    engine.getTextureManager().load("character_walk", "/home/rijad/Projects/roguelike/images/character_walk.png");
    engine.getTextureManager().load("tileset", "/home/rijad/Projects/roguelike/images/tileset.png");
}

int Game::run() {
    std::shared_ptr<Texture> characterIdleTexture = engine.getTextureManager().get("character_idle");
    std::shared_ptr<Texture> characterWalkTexture = engine.getTextureManager().get("character_walk");
    std::shared_ptr<Texture> tilesetTexture = engine.getTextureManager().get("tileset");

    Sprite blacksmith_idle = Sprite(characterIdleTexture.get(), 4, 1, true, 4);
    Sprite blacksmith_walk = Sprite(characterWalkTexture.get(), 4, 1, true, 8);
    Sprite tree = Sprite(tilesetTexture.get(), { UNIT * 6, 0, UNIT, UNIT });
    Sprite grass = Sprite(tilesetTexture.get(), { UNIT * 6, UNIT * 1, UNIT, UNIT });

    SpriteAnimator animator("idle", blacksmith_idle);
    animator.createState("walking", blacksmith_walk);

    Camera& cam = engine.getRenderer().getCamera();
    InputHandler& inputHandler = engine.getInputHandler();

    std::shared_ptr<Map> map = MapBuilder(32, 32)
            .fill(&grass, 16, 9)
            .build();

    double x = 0, y = 0;
    int targetX = 0, targetY = 0;
    bool moving = false;
    bool facingLeft = false;
    bool showMap = true;


    engine.loop([&](double delta) {
        SDL_Log("fps: %lf", engine.getFPS());
        double step = 0.5;

        if(!moving) {
            if (inputHandler.is("right")) {
                targetX += 1;
                moving = true;
                facingLeft = false;
            } else if (inputHandler.is("left")) {
                targetX -= 1;
                moving = true;
                facingLeft = true;
            } else if (inputHandler.is("up")) {
                targetY -= 1;
                moving = true;
            } else if (inputHandler.is("down")) {
                targetY += 1;
                moving = true;
            }
        }

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

        cam.snapFollowTarget({targetX * UNIT, targetY * UNIT }, VIEW_WIDTH, VIEW_HEIGHT);

        if(inputHandler.isPressed("action")) {
            showMap = !showMap;
        }

        if(showMap) {
            map->render(&engine.getRenderer());
        }

        animator.setState(moving ? "walking" : "idle");

        tree.render(&engine.getRenderer(), {UNIT * 2, UNIT * 6});
        tree.render(&engine.getRenderer(), {UNIT * 6, UNIT * 4});
        animator.getSprite().render(&engine.getRenderer(), {(int) x, (int) y}, facingLeft);
    });

    return 0;
}
