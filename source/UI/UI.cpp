#include "UI.h"
#include <iostream>
#include <filesystem>
#include <SDL_image.h>

using namespace std;

UI::~UI() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void UI::run(const float speed) {
    init();
    const auto path = std::filesystem::current_path().parent_path() /= "../resources/Images/";
    Texture issPic = loadTexture(path.u8string() + "ISS.png");
    Texture earthPic = loadTexture(path.u8string() + "2k_earth_daymap.png");

    float windowWidth, windowHeight;
    getWindowSize(windowWidth, windowHeight);

    SDL_FRect satellite = createSatelliteRect();

    SDL_Delay(100);
    bool quit = false;
    Uint32 timePassed = 0;
    Uint32 timeStep = 16; // Target frame duration for 60 FPS

    while (!quit) {
        timePassed = SDL_GetTicks();

        quit = handleEvents(satellite);
        SDL_RenderClear(renderer);
        earthPic.render(renderer, nullptr);
        issPic.render(renderer, &satellite);
        SDL_RenderPresent(renderer);

        // Pass the speed factor to adjust movement
        float x = windowWidth / windowHeight;
        float y = 1;
        updatePosition(x, y, windowWidth, windowHeight, satellite, speed);

        Uint32 frameDuration = SDL_GetTicks() - timePassed;
        if (frameDuration < timeStep) {
            SDL_Delay(timeStep - frameDuration);
        }
    }
}

SDL_FRect UI::createSatelliteRect() {
    SDL_FRect satellite;
    satellite.w = 50;
    satellite.h = 50;
    satellite.x = -satellite.w / 2;
    satellite.y = -satellite.h / 2;
    return satellite;
}

void UI::updatePosition(const float x, const float y, const float windowWidth, const float windowHeight, SDL_FRect &r,
                        const float speed) {
    r.x += x * speed;
    r.y += y * speed;

    if (r.x > windowWidth || r.y > windowHeight) {
        r.x = -r.w / 2;
        r.y = -r.h / 2;
    }
}

bool UI::handleEvents(SDL_FRect &r) {
    bool quit = false;
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }
    return quit;
}

bool UI::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }
    if (!createWindow()) return false;
    if (!createRenderer()) return false;
    if (!initSDLImage()) return false;
    return true;
}

Texture UI::loadTexture(const std::string &filename) const {
    SDL_Texture *imgTexture = IMG_LoadTexture(renderer, filename.c_str());
    if (nullptr == imgTexture) {
        printf("File not found: %s SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
    }

    return {imgTexture};
}

void UI::getWindowSize(float &width, float &height) const {
    int intWidth, intHeight;
    SDL_GetWindowSize(window, &intWidth, &intHeight);
    width = static_cast<float>(intWidth);
    height = static_cast<float>(intHeight);
}

bool UI::createWindow() {
    window = SDL_CreateWindow("Satellite Sniffer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 512,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool UI::createRenderer() {
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool UI::initSDLImage() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}
