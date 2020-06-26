#include "Game.h"
#include "core/SpriteAnimator.h"
#include "core/SpriteAtlas.h"
#include "MapBuilder.h"
#include "TileSet.h"
#include "Hero.h"
#include "Monster.h"
#include "TurnManager.h"
#include "GameManager.h"


Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character", "/home/rijad/Projects/roguelike/images/character.png");
    engine.getTextureManager().load("skeleton", "/home/rijad/Projects/roguelike/images/skeleton.png");
    engine.getTextureManager().load("tileset", "/home/rijad/Projects/roguelike/images/tileset.png");
}

int Game::run() {
    // Textures
    std::shared_ptr<Texture> characterTexture = engine.getTextureManager().get("character");
    std::shared_ptr<Texture> skeletonTexture = engine.getTextureManager().get("skeleton");
    std::shared_ptr<Texture> tileSetTexture = engine.getTextureManager().get("tileset");

    // Turn indicator sprite
    Sprite turnIndicatorSprite(tileSetTexture, {
            { 5 * UNIT, 3 * UNIT, UNIT, UNIT },
            { 6 * UNIT, 3 * UNIT, UNIT, UNIT }
    }, true, 1);

    // Character SpriteAtlas
    SpriteAtlas characterSprites(characterTexture);
    characterSprites.markGrid("idle", { 0,0,UNIT,UNIT }, 4, 1, true, 4);
    characterSprites.markGrid("walk", { 0,UNIT,UNIT,UNIT }, 4, 1, true, 16);

    // Skeleton SpriteAtlas
    SpriteAtlas skeletonSprites(skeletonTexture);
    skeletonSprites.markGrid("idle", { 0,0,UNIT,UNIT }, 4, 1, true, 4);
    skeletonSprites.markGrid("walk", { 0,UNIT,UNIT,UNIT }, 4, 1, true, 16);

    // TileSet SpriteAtlas
    SpriteAtlas tileSetSprites(tileSetTexture);
    tileSetSprites.mark("tree", {UNIT * 6, 0, UNIT, UNIT });
    tileSetSprites.mark("grass", {UNIT * 6, UNIT * 1, UNIT, UNIT });

    // Character Animator
    SpriteAnimator characterAnimator("idle", *characterSprites.get("idle"));
    characterAnimator.createState("walk", *characterSprites.get("walk"));

    // Skeleton Animator
    SpriteAnimator skeletonAnimator("idle", *skeletonSprites.get("idle"));
    skeletonAnimator.createState("walk", *skeletonSprites.get("walk"));

    // TileSet
    TileSet tileSet(tileSetSprites);
    tileSet.put("grass", "grass", TileType::GROUND);
    tileSet.put("tree", "tree", TileType::WALL);

    // Camera and Input handler
    Camera& cam = engine.getRenderer().getCamera();
    InputHandler& inputHandler = engine.getInputHandler();

    // Map building
    std::shared_ptr<Map> map = MapBuilder(32, 32, UNIT)
            .fill(tileSet.get("grass"), 0, 0, 16, 9)
            .addLayer()
            .fill(tileSet.get("tree"), 0, 0, 1, 9)
            .fill(tileSet.get("tree"), 0, 0, 16, 1)
            .fill(tileSet.get("tree"), 15, 0, 1, 9)
            .fill(tileSet.get("tree"), 0, 8, 16, 1)
            .fill(tileSet.get("tree"), 4, 4, 2, 2)
            .put(tileSet.get("tree"), {1, 1})
            .put(tileSet.get("tree"), {3, 7})
            .put(tileSet.get("tree"), {9, 5})
            .build();

    GameManager gameManager(engine, map, UNIT);
    gameManager.createHero({8, 4}, characterAnimator);
    gameManager.createMonster({12, 2}, skeletonAnimator);
    gameManager.createMonster({3, 5}, skeletonAnimator);
    gameManager.createMonster({1, 2}, skeletonAnimator);
    gameManager.createMonster({6, 6}, skeletonAnimator);

    TurnManager turnManager (gameManager.getEntities());

    engine.loop([&](double delta) {
        if(!turnManager.hasAction()) {
            turnManager.next();
        }
        turnManager.update();

        cam.snapFollowTarget(gameManager.getHero()->getPosition(), VIEW_WIDTH, VIEW_HEIGHT);

        map->render(&engine.getRenderer());
        for(auto& entity : gameManager.getEntities()) {
            entity->render(&engine.getRenderer());
        }
        turnIndicatorSprite.render(&engine.getRenderer(), turnManager.getCurrentEntity()->getTruePosition());
    });

    return 0;
}
