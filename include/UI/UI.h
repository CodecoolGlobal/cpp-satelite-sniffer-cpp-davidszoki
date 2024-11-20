#pragma once
#include <GPS.h>
#include <SDL.h>
#include <string>
#include "Texture.h"

class UI {
public:
    UI() : window(nullptr), renderer(nullptr) {
    }

    ~UI();

    void run(const int &speed = 1);

    static bool handleEvents();

    void updatePosition(const float &x, const float &y, const float &windowWidth, SDL_FRect &r);

    static SDL_FRect createSatelliteRect();

    std::pair<float, float> convertGPStoPixels(const GPS &gps, const float &windowWidth, const float &windowHeight);

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
