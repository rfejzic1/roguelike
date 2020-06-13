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
    int framesPerSecond = 1;
    bool loop = false;
public:
    Sprite();
    explicit Sprite(Texture* texture);
    Sprite(Texture* texture, const Rect& rect);
    Sprite(Texture *texture, const std::vector<Rect> &frames, bool loop, int framesPerSecond);
    Sprite(Texture *texture, int cols, int rows, bool loop, int framesPerSecond);
    void render(Renderer *renderer, const Vector2D &position, bool flipped = false);
    void reset();
    void setLoop(bool loop);
};
