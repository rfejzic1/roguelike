#include "Game.h"
#include "core/SpriteAnimator.h"
#include "core/SpriteAtlas.h"
#include "MapBuilder.h"
#include "TileSet.h"
#include "Hero.h"
#include "core/Timer.h"

#include <ctime>

Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character", "/home/rijad/Projects/roguelike/images/character.png");
    engine.getTextureManager().load("tileset", "/home/rijad/Projects/roguelike/images/tileset.png");
}

int Game::run() {
    std::shared_ptr<Texture> characterTexture = engine.getTextureManager().get("character");
    std::shared_ptr<Texture> tileSetTexture = engine.getTextureManager().get("tileset");

    SpriteAtlas characterSprites(characterTexture);
    characterSprites.markGrid("idle", { 0,0,UNIT,UNIT }, 4, 1, true, 4);
    characterSprites.markGrid("walk", { 0,UNIT,UNIT,UNIT }, 4, 1, true, 4);

    SpriteAtlas tileSetSprites(tileSetTexture);
    tileSetSprites.mark("tree", {UNIT * 6, 0, UNIT, UNIT });
    tileSetSprites.mark("grass", {UNIT * 6, UNIT * 1, UNIT, UNIT });

    SpriteAnimator animator("idle", *characterSprites.get("idle"));
    animator.createState("walking", *characterSprites.get("walk"));

    std::shared_ptr<Entity> character = std::make_shared<Hero>(Vector2D{8 * UNIT, 4 * UNIT}, animator);

    TileSet tileSet(tileSetSprites);
    tileSet.put("grass", "grass", false);
    tileSet.put("tree", "tree", true);

    Camera& cam = engine.getRenderer().getCamera();
    InputHandler& inputHandler = engine.getInputHandler();

    srand(time(nullptr));
    auto randomPos = [&](int rangeX, int rangeY) {
        return Vector2D(rand() % rangeX, rand() % rangeY);
    };

    std::shared_ptr<Map> map = MapBuilder(32, 32, UNIT)
            .fill(tileSet.get("grass"), 16, 9)
            .addLayer()
            .put(tileSet.get("tree"), randomPos(16, 9))
            .put(tileSet.get("tree"), randomPos(16, 9))
            .put(tileSet.get("tree"), randomPos(16, 9))
            .build();

    std::shared_ptr<Action> currentAction = nullptr;

    engine.loop([&](double delta) {
//        SDL_Log("fps: %lf", engine.getFPS());

        if(!currentAction) {
            currentAction = character->takeTurn();
        }

        ActionState actionState = currentAction->perform();
        if(actionState == ActionState::DONE) {
            std::shared_ptr<ActionResult> result = currentAction->getResult();
            SDL_Log("Result: %d", *result);
            currentAction = nullptr;
        }

        cam.snapFollowTarget(character->getPosition(), VIEW_WIDTH, VIEW_HEIGHT);

        map->render(&engine.getRenderer());
        character->render(&engine.getRenderer());
    });

    return 0;
}
