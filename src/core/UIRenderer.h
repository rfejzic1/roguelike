#pragma once

class Renderer;
class UIElement;

class UIRenderer {
    Renderer* renderer;
public:
    explicit UIRenderer(Renderer* renderer);
    void render(UIElement *uiElement);
    Renderer* getRenderer();
};
