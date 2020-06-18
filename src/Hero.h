#pragma once

#include "Entity.h"
#include <random>

// TODO: When an Entity takes a turn, it produces an Action;
//       Keep the Action in an attribute called currentAction*;
//       Have the main game loop iterate over entities, and
//       execute Action objects.
//       Action objects themselves have a state: RUNNING, DONE
//       An Action object has a method celled "perform" which based on the
//       state of the Action executes different code. This way, when the main
//       game loop invokes the Action, it completes a single iteration of it.
//       The START state changes on the first invocation to RUNNING and explicitly
//       changes from RUNNING to DONE.
//       When an action is done, the entity currentAction* attribute gets set to nullptr,
//       so when the Entity takes another turn, it produces a new Action;
//       This implies, that the Entity would have a "takeTurn" method which produces an Action
//       and would keep a reference to that Action. The Entity itself has no update method
//       but the Action object behaves like a method with state...

/*

 abstract Action {
    ptr<ActionResult> result;

    Action(Entity* entity, ...) : entity(entity) { ... }

    ActionState perform() {
        // ...
        if done {
            return ActionState::DONE;
        }

        return ActionState::RUNNING;
    }

    ptr<ActionResult> getResult() { ... }

 }

 // Meanwhile somewhere in the game loop...
 while isRunning {
    // ...

    for entity in entities {
        ptr<Action> action = entity.getCurrentAction();
        if !action {
            continue;
        }
        ActionState state = action->perform();
        if state == ActionState::DONE {
            shared<ActionResult> result = action->getResult();
        }
    }

    // The TurnManager would actually allow only for one Entity to have an action at a time???
    // ...
 }

*/

class Hero : public Entity {
    GameEngine& engine;
public:
    Hero(GameEngine& gameEngine, const Vector2D &position, const SpriteAnimator &animator);
    std::shared_ptr<Action> takeTurn() override;
    friend class PlayerInputAction;
};
