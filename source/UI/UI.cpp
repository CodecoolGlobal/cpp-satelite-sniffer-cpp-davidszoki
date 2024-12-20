#include <UI.h>
#include <PythonScriptExecutor.h>
#include <SDL_image.h>
#include <Utils.h>
#include <SDL_ttf.h>

using namespace std;

UI::UI(const int &width, const int &height, ISatelliteSniffer &sniffer)
    : window(nullptr), renderer(nullptr), width(width), height(height), sniffer(sniffer) {
}

UI::~UI() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void UI::run(const int &speed) {
    init(width, height);
    Texture background = createTexture("2k_earth_daymap");
    vector<Texture> satelliteTextures;
    vector<SDL_FRect> satelliteUIElements;
    createSatelliteUIElements(satelliteTextures, satelliteUIElements);
    TTF_Font *Sans = TTF_OpenFont((path / ".." / "Fonts" / "Roboto-Bold.ttf").u8string().c_str(), 20);
    SDL_FRect text_rect = creteTextRect();

    bool quit = false;
    const Uint32 milliseconds = speed >= 1 ? 500 * speed : 500 / abs(speed);
    SDL_Delay(100); // Small delay before the loop starts

    // Start the main loop
    while (!quit) {
        Uint32 timePassed = SDL_GetTicks(); // Start time of the frame
        auto updateTime = timePassed * milliseconds;
        quit = handleEvents();

        string text = "GMT " + Utils::getTimeString(updateTime);
        SDL_Surface *surface = TTF_RenderText_Solid(Sans, text.c_str(), {255, 0, 0});
        SDL_Texture *textTexture = createTextTexture(surface);

        SDL_RenderClear(renderer);
        renderTextures(background, satelliteTextures, satelliteUIElements);
        SDL_RenderCopyF(renderer, textTexture, NULL, &text_rect);
        SDL_RenderPresent(renderer);

        sniffer.updatePositions(width, height, updateTime);
        updatePositions(satelliteUIElements);

        SDL_DestroyTexture(textTexture);
    }
    TTF_CloseFont(Sans);
}

void UI::createSatelliteUIElements(vector<Texture> &satelliteTextures, vector<SDL_FRect> &satelliteUIElements) {
    for (auto &sat: sniffer.getSatellites()) {
        satelliteTextures.push_back(createTexture(sat.getTLE().name));
        SDL_FRect rect = createSatelliteRect();
        satelliteUIElements.push_back(rect);
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

SDL_FRect UI::creteTextRect() {
    SDL_FRect m_rect;
    m_rect.h = 40;
    m_rect.w = 300;
    m_rect.x = width / 2 - m_rect.w / 2;
    m_rect.y = m_rect.h / 2;
    return m_rect;
}

Texture UI::createTexture(const std::string &filename) {
    return loadTexture(path.u8string() + filename + ".png");
}

void UI::renderTexture(Texture &texture, SDL_FRect *rect) {
    texture.render(renderer, rect);
}

void UI::renderTextures(Texture &background, vector<Texture> &satelliteTextures,
                        vector<SDL_FRect> &satelliteUIElements) {
    renderTexture(background, nullptr);
    for (int i = 0; i < satelliteTextures.size(); i++) {
        renderTexture(satelliteTextures[i], &satelliteUIElements[i]);
    }
}

SDL_Texture *UI::createTextTexture(SDL_Surface *surface) {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void UI::updatePosition(const pair<float, float> &xy, SDL_FRect &r) {
    if (r.x + r.w / 2 > width + r.w) {
        r.x = -(xy.first - r.w / 2);
        r.y = xy.second - r.h / 2;
    }

    r.x = xy.first - r.w / 2;
    r.y = xy.second - r.h / 2;
}

void UI::updatePositions(vector<SDL_FRect> &satelliteUIElements) {
    auto satellites = sniffer.getSatellites();
    for (int i = 0; i < satellites.size(); i++) {
        updatePosition(satellites[i].getXY(), satelliteUIElements[i]);
    }
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

bool UI::init(const int &width, const int &height) {
    TTF_Init();
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        Utils::printLine("SDL_Init Error: ", SDL_GetError());
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (!createWindow(width, height)) return false;
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

bool UI::createWindow(const int &width, const int &height) {
    window = SDL_CreateWindow("Satellite Sniffer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        Utils::printLine("SDL_CreateWindow Error: ", SDL_GetError());
        return false;
    }
    return true;
}

bool UI::createRenderer() {
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        Utils::printLine("SDL_CreateRenderer Error: ", SDL_GetError());
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
