#include "UIRenderer.h"
#include "UIElement.h"

UIRenderer::UIRenderer(Renderer *renderer) : renderer(renderer) {}

void UIRenderer::render(UIElement *uiElement) {
    uiElement->render(this);
}

Renderer *UIRenderer::getRenderer() {
    return renderer;
}
