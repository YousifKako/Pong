#pragma once

#include "GameObject.hpp"


class Player : public GameObject
{
private:
    uint16_t xPos = 20;

public:
    uint16_t y = 250;

    Player(const char* texturesheet, SDL_Renderer* rend,
        uint16_t x, uint16_t y, uint16_t w, uint16_t h,
        uint16_t xPos);
    ~Player();
    void update();
};