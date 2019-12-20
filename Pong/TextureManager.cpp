#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* filename, SDL_Renderer* rend)
{
    SDL_Surface* surface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    return texture;
}