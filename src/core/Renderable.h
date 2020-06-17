#pragma once

class Renderer;

struct Renderable {
    virtual void render(Renderer* renderer) = 0;
    virtual ~Renderable() = default;
};
