#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "Rect.h"
#include "Camera.h"

class Texture;
class GameEngine;

class Renderer {
    const int VIEW_WIDTH;
    const int VIEW_HEIGHT;
    const int SCALE;

    SDL_Renderer* renderer = nullptr;
    GameEngine* gameEngine = nullptr;
    Camera camera;

    explicit Renderer(SDL_Window* window, int viewWidth, int viewHeight, int scale = 1);
    SDL_Renderer* getSDLRenderer();
    void setGameEngine(GameEngine *gameEngine);
public:
    void clear();
    void render(Texture *texture, Rect *dest);
    void render(Texture *texture, Rect *src, Rect *dest, bool flipped = false);
    void renderText(const std::string &text, const Vector2D &position, const SDL_Color &color);
    void update();
    double getFPS() const;
    void setCamera(const Camera& newCamera);
    Camera& getCamera();
    int getViewWidth();
    int getViewHeight();
    ~Renderer();
    friend class GameEngine;
};
