#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* rend)
{
    this->renderer = rend;
    this->objectTexture = TextureManager::loadTexture(texturesheet, rend);
}

GameObject::~GameObject()
{

}

//void GameObject::update()
//{
//    this->destRect.x = this->x;
//    this->destRect.y = this->y;
//}

void GameObject::render()
{
    SDL_RenderCopy(this->renderer, this->objectTexture, &this->srcRect, &this->destRect);
}