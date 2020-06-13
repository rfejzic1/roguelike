#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite() : texture(nullptr), frameCount(0) {}

Sprite::Sprite(Texture *texture) : texture(texture), frameCount(1) {
    frames.emplace_back(0, 0, texture->getWidth(), texture->getHeight());
}

Sprite::Sprite(Texture *texture, const Rect &rect) : texture(texture), frameCount(1) {
    frames.emplace_back(rect);
}

Sprite::Sprite(Texture *texture, const std::vector<Rect> &frames, bool loop, int framesPerSecond)
    : texture(texture), frames(frames), frameCount(frames.size()), framesPerSecond(framesPerSecond), loop(loop) {}

Sprite::Sprite(Texture *texture, int cols, int rows, bool loop, int framesPerSecond)
    : texture(texture), framesPerSecond(framesPerSecond), loop(loop)
{
    int cellWidth = texture->getWidth() / cols;
    int cellHeight = texture->getHeight() / rows;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            frames.emplace_back(j * cellWidth, i * cellHeight, cellWidth, cellHeight);
        }
    }

    frameCount = frames.size();
}

void Sprite::render(Renderer *renderer, const Vector2D &position, bool flipped) {
    if(frameCount == 0) {
        return;
    }

    double frameRate = renderer->getFPS() / framesPerSecond;

    rendererFrame += 1;
    if(rendererFrame > frameRate) {
        if(loop) {
            frameIndex = (frameIndex + 1) % frameCount;
        } else {
            if(frameIndex < frameCount - 1) {
                frameIndex += 1;
            }
        }
        rendererFrame = 0;
    }
    Rect& frame = frames[frameIndex];
    Rect dest = { position.x, position.y, frame.width, frame.height };
    renderer->render(texture, &frames[frameIndex], &dest, flipped);
}

void Sprite::reset() {
    frameIndex = 0;
}

void Sprite::setLoop(bool loopFrames) {
    loop = loopFrames;
}
