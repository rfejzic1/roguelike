#include "Game.h"
#include "core/SpriteAnimator.h"
#include "core/SpriteAtlas.h"
#include "MapBuilder.h"
#include "TileSet.h"
#include "Hero.h"
#include "TurnManager.h"
#include "GameManager.h"


Game::Game() : engine(VIEW_WIDTH, VIEW_HEIGHT, SCALE) {
    engine.getTextureManager().load("character", "./images/character.png");
    engine.getTextureManager().load("skeleton", "./images/skeleton.png");
    engine.getTextureManager().load("tileset", "./images/tileset.png");
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
    tileSetSprites.mark("sign", {UNIT * 6, UNIT * 2, UNIT, UNIT});

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

    // GameManager setup
    GameManager gameManager(engine, map, UNIT);
    gameManager.createHero({8, 4}, characterAnimator);
    gameManager.createMonster({12, 2}, skeletonAnimator);
    gameManager.createMonster({3, 5}, skeletonAnimator);
    gameManager.createMonster({1, 2}, skeletonAnimator);
    gameManager.createMonster({6, 6}, skeletonAnimator);

    gameManager.createMapObject(
            {7, 4},
            tileSetSprites.get("sign"),
            true);

    TurnManager turnManager (gameManager.getEntities());

    engine.loop([&](double delta) {
        if(!turnManager.hasAction()) {
            turnManager.next();
        }
        turnManager.update();

        engine.getRenderer().getCamera().snapFollowTarget(gameManager.getHero()->getTruePosition(), VIEW_WIDTH, VIEW_HEIGHT);

        gameManager.render();
        turnIndicatorSprite.render(&engine.getRenderer(), turnManager.getCurrentEntity()->getTruePosition());

        engine.getRenderer().renderText("The Valley of Heroes", { 8, 8 }, { 0x00, 0x00, 0x00 });
    });

    return 0;
}
