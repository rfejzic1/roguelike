#pragma once

#include "Vector2D.h"
#include "UIRenderer.h"

class UIElement {
protected:
    UIRenderer* uiRenderer;
    Vector2D position;
public:
    inline UIElement(UIRenderer* uiRenderer, const Vector2D& position);
    virtual void render(UIRenderer* uiRenderer) = 0;
    inline Vector2D getPosition();
    inline void setPosition(const Vector2D& newPosition);
};

UIElement::UIElement(UIRenderer *uiRenderer, const Vector2D &position)
    : uiRenderer(uiRenderer), position(position) {}

Vector2D UIElement::getPosition() {
    return position;
}

void UIElement::setPosition(const Vector2D &newPosition) {
    position = newPosition;
}
