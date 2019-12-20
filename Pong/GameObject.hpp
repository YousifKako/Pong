#pragma once
#include <stdint.h>

#include <SDL_image.h>


class GameObject
{
protected:
    SDL_Texture* objectTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Rect srcRect = { };
    SDL_Rect destRect = { };

public:
    GameObject(const char* texturesheet, SDL_Renderer* rend);
    ~GameObject();
    void render();
};