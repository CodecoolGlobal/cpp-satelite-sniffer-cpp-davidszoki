#include "Texture.h"

Texture::Texture(SDL_Texture* texture)
{
    this->texture = texture;
}

Texture::~Texture()
{
    if(texture) SDL_DestroyTexture(texture);
}

void Texture::render(SDL_Renderer* renderer, const SDL_FRect* pos)
{
    SDL_RenderCopyF(renderer, texture, NULL, pos);
}