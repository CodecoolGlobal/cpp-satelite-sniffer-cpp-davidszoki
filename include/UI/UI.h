#pragma once
#include <SDL.h>
#include <string>
#include "Texture.h"

class UI {
public:
    UI() : window(nullptr), renderer(nullptr) {
    }

    ~UI();

    void run();

    static bool handleEvents();

    void updatePosition(float x, float y, float windowWidth, float windowHeight, SDL_FRect &r);

    static SDL_FRect createSatelliteRect();

    bool init();

    Texture loadTexture(const std::string &filename) const;

    void getWindowSize(float &width, float &height) const;

    SDL_Renderer *getRenderer() { return renderer; }

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool createWindow();

    bool createRenderer();

    static bool initSDLImage();
};
