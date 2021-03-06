#pragma once

#include <memory>

enum class ActionState {
    RUNNING, DONE
};

enum class ActionResult {
    GOOD, BAD
};

class Action {
protected:
    std::shared_ptr<ActionResult> result = nullptr;
    std::shared_ptr<Action> chainAction = nullptr;
public:
    virtual ActionState perform() = 0;
    virtual std::shared_ptr<ActionResult> getResult() {
        auto temp = result;
        result = nullptr;
        return temp;
    };
    bool hasChainAction() {
        return chainAction != nullptr;
    }
    std::shared_ptr<Action> getChainAction() {
        return chainAction;
    }
};
