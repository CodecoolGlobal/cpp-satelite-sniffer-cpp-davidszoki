#pragma once
#include <SDL_image.h>
#include <memory>

class Texture {
public:
    Texture(SDL_Texture *texture);
    Texture(const Texture& other);
    ~Texture();
    Texture& operator=(const Texture& other);
    void render(SDL_Renderer *renderer, const SDL_FRect *pos) const;
private:
    std::shared_ptr<SDL_Texture> texture;
};
