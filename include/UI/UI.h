#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <filesystem>
#include <ISatelliteSniffer.h>
#include <Texture.h>

const auto path = std::filesystem::current_path().parent_path() /= "../resources/Images/";

class UI {
public:
    UI(const int &width, const int &height, ISatelliteSniffer &sniffer);

    ~UI();

    void run(const int &speed = 1);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width, height;
    ISatelliteSniffer &sniffer;

    bool createWindow(const int &width, const int &height);

    bool createRenderer();

    static bool initSDLImage();

    static bool handleEvents();

    void updatePosition(const std::pair<float, float> &xy, SDL_FRect &r);

    void updatePositions(std::vector<SDL_FRect> &satelliteUIElements);

    SDL_FRect createSatelliteRect();

    SDL_FRect creteTextRect();

    void createSatelliteUIElements(std::vector<Texture> &satelliteTextures,
                                   std::vector<SDL_FRect> &satelliteUIElements);

    Texture createTexture(const std::string &filename);

    SDL_Texture *createTextTexture(SDL_Surface *surface);

    std::vector<Texture> createSatelliteTextures();

    void renderTexture(Texture &texture, SDL_FRect *rect);

    void renderTextures(Texture &background, std::vector<Texture> &satelliteTextures,
                        std::vector<SDL_FRect> &satelliteUIElements);

    bool init(const int &width, const int &height);

    Texture loadTexture(const std::string &filename) const;

    SDL_Renderer *getRenderer() { return renderer; }
};
