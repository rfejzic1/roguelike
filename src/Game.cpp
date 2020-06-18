#include "Game.h"
#include "core/SpriteAnimator.h"
#include "core/SpriteAtlas.h"
#include "MapBuilder.h"
#include "TileSet.h"
#include "Hero.h"
#include "Monster.h"
#include "TurnManager.h"


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

    // Entities
    std::shared_ptr<Entity> character = std::make_shared<Hero>(engine, Vector2D{8 * UNIT, 4 * UNIT}, characterAnimator);
    std::shared_ptr<Entity> skeleton = std::make_shared<Monster>(Vector2D{12 * UNIT, 2 * UNIT}, skeletonAnimator);
    std::shared_ptr<Entity> skeleton2 = std::make_shared<Monster>(Vector2D{3 * UNIT, 5 * UNIT}, skeletonAnimator);
    std::shared_ptr<Entity> skeleton3 = std::make_shared<Monster>(Vector2D{1 * UNIT, 2 * UNIT}, skeletonAnimator);
    std::shared_ptr<Entity> skeleton4 = std::make_shared<Monster>(Vector2D{6 * UNIT, 6 * UNIT}, skeletonAnimator);

    // TileSet
    TileSet tileSet(tileSetSprites);
    tileSet.put("grass", "grass", false);
    tileSet.put("tree", "tree", true);

    // Camera and Input handler
    Camera& cam = engine.getRenderer().getCamera();
    InputHandler& inputHandler = engine.getInputHandler();

    // Map building
    std::shared_ptr<Map> map = MapBuilder(32, 32, UNIT)
            .fill(tileSet.get("grass"), 16, 9)
            .addLayer()
            .put(tileSet.get("tree"), {1, 1})
            .put(tileSet.get("tree"), {3, 7})
            .put(tileSet.get("tree"), {9, 5})
            .build();

    TurnManager turnManager ({ character, skeleton, skeleton2, skeleton3, skeleton4 });

    engine.loop([&](double delta) {
        SDL_Log("fps: %lf", engine.getFPS());

        turnManager.update();

        cam.snapFollowTarget(character->getPosition(), VIEW_WIDTH, VIEW_HEIGHT);

        map->render(&engine.getRenderer());
        for(auto& entity : turnManager.getEntities()) {
            entity->render(&engine.getRenderer());
        }
    });

    return 0;
}
