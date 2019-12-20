#include "Ball.hpp"

Ball::Ball(const char* texturesheet, SDL_Renderer* rend,
    uint16_t x, uint16_t y, uint16_t w, uint16_t h)
    : GameObject(texturesheet, rend)
{
    this->srcRect.h = h;
    this->srcRect.w = w;
    this->srcRect.x = x;
    this->srcRect.y = y;

    this->destRect.h = 12;
    this->destRect.w = 12;
}

Ball::~Ball()
{

}

void Ball::update()
{
    this->destRect.x = this->x;
    this->destRect.y = this->y;
}