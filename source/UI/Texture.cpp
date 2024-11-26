#include "Texture.h"
#include <memory>

Texture::Texture(SDL_Texture* texture)
    : texture(std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture)) {}

Texture::~Texture() = default;

Texture::Texture(const Texture& other) : texture(other.texture) {}

Texture& Texture::operator=(const Texture& other) {
    if (this == &other) return *this;
    texture = other.texture;
    return *this;
}

void Texture::render(SDL_Renderer* renderer, const SDL_FRect* pos) const {
    SDL_RenderCopyF(renderer, texture.get(), nullptr, pos);
}
