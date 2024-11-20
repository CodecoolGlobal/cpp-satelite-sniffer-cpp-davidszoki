#include "UI.h"
#include <iostream>
#include <filesystem>
#include <PythonScriptExecutor.h>
#include <SDL_image.h>
#include <TLEtoGPS.h>

using namespace std;

UI::~UI() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void UI::run(const int &speed) {
    init();
    const auto path = std::filesystem::current_path().parent_path() /= "../resources/Images/";
    Texture issPic = loadTexture(path.u8string() + "ISS.png");
    Texture earthPic = loadTexture(path.u8string() + "2k_earth_daymap.png");

    float windowWidth, windowHeight;
    getWindowSize(windowWidth, windowHeight);

    SDL_FRect satellite = createSatelliteRect();

    SDL_Delay(100);
    bool quit = false;
    const Uint32 timeStep = 16;
    Uint32 milliseconds = speed >= 1 ? 500 * speed : 500 / abs(speed);

    while (!quit) {
        Uint32 timePassed = SDL_GetTicks();
        quit = handleEvents();

        SDL_RenderClear(renderer);
        earthPic.render(renderer, nullptr);
        issPic.render(renderer, &satellite);
        SDL_RenderPresent(renderer);

        auto gpsnow = TLEtoGPS::convertTLEToGPSAtTimeWindow("iss_last_tle.txt", timePassed * milliseconds);
        auto xy = convertGPStoPixels(gpsnow, windowWidth, windowHeight);

        updatePosition(xy.first, xy.second, windowWidth, satellite);

        while (timePassed + timeStep > SDL_GetTicks()) {
            SDL_Delay(0);
        }
    }
}

SDL_FRect UI::createSatelliteRect() {
    SDL_FRect satellite;
    satellite.w = 50;
    satellite.h = 50;
    satellite.x = -satellite.w;
    satellite.y = -satellite.h;
    return satellite;
}

pair<float, float> UI::convertGPStoPixels(const GPS &gps, const float &windowWidth, const float &windowHeight) {
    pair<float, float> xy = {0, 0};
    const auto radius = windowWidth / (2 * M_PI);

    auto latRad = gps.latitude;
    auto lonRad = gps.longitude + M_PI;
    auto yFromEquator = radius * log(tan(M_PI / 4 + latRad / 2));

    xy.first = lonRad * radius;
    xy.second = windowHeight / 2 - yFromEquator;
    return xy;
}


void UI::updatePosition(const float &x, const float &y, const float &windowWidth, SDL_FRect &r) {
    if (r.x + r.w / 2 > windowWidth + r.w) {
        r.x = -(x - r.w / 2);
        r.y = y - r.h / 2;
    }

    r.x = x - r.w / 2;
    r.y = y - r.h / 2;
}

bool UI::handleEvents() {
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
