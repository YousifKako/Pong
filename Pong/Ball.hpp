#pragma once

#include "GameObject.hpp"


class Ball : public GameObject
{
public:
    uint16_t x = 900 / 2;
    uint16_t y = 600 / 2;

    Ball(const char* texturesheet, SDL_Renderer* rend,
        uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    ~Ball();
    void update();
};