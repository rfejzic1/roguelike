#pragma once

#include <vector>
#include "Rect.h"
#include "Vector2D.h"

class Texture;
class Renderer;

class Sprite {
    Texture* texture = nullptr;
    std::vector<Rect> frames;
    int frameIndex = 0;
    int frameCount = 0;
    int rendererFrame = 0;
    int frameRate = 0;
public:
    Sprite(Texture* texture);
    Sprite(Texture* texture, const Rect& rect);
    Sprite(Texture* texture, const std::vector<Rect>& frames, int frameRate);
    Sprite(Texture* texture, int cols, int rows, int frameRate);
    void render(Renderer* renderer, const Vector2D& position);
};
