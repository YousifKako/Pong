#include "Player.hpp"

Player::Player(const char* texturesheet, SDL_Renderer* rend,
    uint16_t x, uint16_t y, uint16_t w, uint16_t h,
    uint16_t xPos)
    : GameObject(texturesheet, rend)
{
    this->xPos = xPos;

    this->srcRect.h = h;
    this->srcRect.w = w;
    this->srcRect.x = x;
    this->srcRect.y = y;

    this->destRect.h = 84;
    this->destRect.w = 10;
    this->destRect.x = this->xPos;
}

Player::~Player()
{

}

void Player::update()
{
    this->destRect.y = this->y;
}