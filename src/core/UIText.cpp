#include "UIText.h"
#include "Texture.h"

UIText::UIText(UIRenderer *uiRenderer, const Vector2D &position, TTF_Font *font, const std::string &content,
               const Color &color)
    : UIElement(uiRenderer, position), font(font), color(color), texture(nullptr)
{
    setContent(content);
}

void UIText::generateTexture() {
    Texture* newTexture = Texture::createFromText(uiRenderer->getRenderer(), font, content, color);
    if(newTexture) {
        delete texture;
        texture = newTexture;
    }
}

std::string UIText::getContent() {
    return content;
}

void UIText::setContent(const std::string& textContent) {
    if(content != textContent) {
        content = textContent;
        generateTexture();
    }
}

UIText::~UIText() {
    delete texture;
    texture = nullptr;
}

void UIText::render(UIRenderer *uiRenderer) {
    Rect dest = { position.x, position.y, texture->getWidth(), texture->getHeight() };
    uiRenderer->getRenderer()->render(texture, &dest);
}

Color UIText::getColor() {
    return color;
}

void UIText::setColor(const Color& newColor) {
    color = newColor;
}
