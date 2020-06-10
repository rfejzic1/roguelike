#include <iostream>
#include <SDL2/SDL.h>

int main() {
    const int VIEW_WIDTH = 320;
    const int VIEW_HEIGHT = 240;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, VIEW_WIDTH, VIEW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
