#pragma once

#include <string>
#include "UIElement.h"
#include "Color.h"
#include <SDL2/SDL_ttf.h>

class Texture;

class UIText : public UIElement {
    TTF_Font* font;
    std::string content;
    Color color;
    Texture* texture;

    void generateTexture();
public:
    UIText(UIRenderer *uiRenderer, const Vector2D &position, TTF_Font *font, const std::string &content, const Color &color);
    void render(UIRenderer *uiRenderer) override;
    std::string getContent();
    void setContent(const std::string& content);
    Color getColor();
    void setColor(const Color& newColor);
    ~UIText();
};
