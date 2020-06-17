#include "Game.h"
#include "core/SpriteAnimator.h"
#include "core/SpriteAtlas.h"
#include "MapBuilder.h"
#include "TileSet.h"

Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character", "/home/rijad/Projects/roguelike/images/character.png");
    engine.getTextureManager().load("tileset", "/home/rijad/Projects/roguelike/images/tileset.png");
}

int Game::run() {
    std::shared_ptr<Texture> characterTexture = engine.getTextureManager().get("character");
    std::shared_ptr<Texture> tileSetTexture = engine.getTextureManager().get("tileset");

    SpriteAtlas characterSprites(characterTexture);
    characterSprites.markGrid("idle", { 0,0,UNIT,UNIT }, 4, 1, true, 4);
    characterSprites.markGrid("walk", { 0,UNIT,UNIT,UNIT }, 4, 1, true, 8);

    SpriteAtlas tileSetSprites(tileSetTexture);
    tileSetSprites.mark("tree", {UNIT * 6, 0, UNIT, UNIT });
    tileSetSprites.mark("grass", {UNIT * 6, UNIT * 1, UNIT, UNIT });

    SpriteAnimator animator("idle", *characterSprites.get("idle"));
    animator.createState("walking", *characterSprites.get("walk"));

    TileSet tileSet(tileSetSprites);
    tileSet.put("grass", "grass", false);
    tileSet.put("tree", "tree", true);

    Camera& cam = engine.getRenderer().getCamera();
    InputHandler& inputHandler = engine.getInputHandler();

    std::shared_ptr<Map> map = MapBuilder(32, 32)
            .fill(tileSet.get("grass"), 16, 9)
            .put(tileSet.get("tree"), { 2, 6 })
            .put(tileSet.get("tree"), { 6, 4 })
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
        animator.getSprite().render(&engine.getRenderer(), {(int) x, (int) y}, facingLeft);
    });

    return 0;
}
