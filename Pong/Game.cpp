#include <iostream>

#include <SDL.h>
#include <SDL_net.h>

#include "Game.hpp"


Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL was unable to be initialized ERR: " << SDL_GetError() << std::endl;
        throw EXIT_FAILURE;
    }
    std::cerr << "SDL has been initialized" << std::endl;


    this->window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_SHOWN);
    if (this->window < 0)
    {
        std::cerr << "SDL Window was unable to be initialized ERR: " << SDL_GetError() << std::endl;
        throw EXIT_FAILURE;
    }
    std::cerr << "SDL Window has been initialized"  << std::endl;


    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if (this->renderer < 0)
    {
        std::cerr << "SDL Renderer was unable to be initialized ERR: " << SDL_GetError() << std::endl;
        throw EXIT_FAILURE;
    }
    SDL_SetRenderDrawColor(this->renderer, 8, 8, 36, 255);
    //SDL_SetRenderDrawColor(this->renderer, 29, 29, 128, 255);
    std::cerr << "SDL Renderer has been initialized" << std::endl;

    this->isRunning = true;

    //if (SDLNet_Init() < 0)
    //{
    //    std::cerr << "SDL_net unable to be initialized ERR: " << SDLNet_GetError() << std::endl;
    //    throw EXIT_FAILURE;
    //}
    //SDLNet_ResolveHost(&this->ip, NULL, port);
    //this->server = SDLNet_TCP_Open(&ip);
}

Game::~Game()
{
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    SDLNet_Quit();

    std::cerr << "Exiting..." << std::endl;
}

void Game::handleEvents()
{
    /* Handling SDL Quit */
    
    SDL_Event event = { };
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            this->isRunning = false;
            break;

        default:
            break;
    }

}

void Game::update()
{

}

void Game::render()
{
    SDL_RenderClear(this->renderer);

    /* Add objects to render */

    SDL_RenderPresent(this->renderer);
}

bool Game::running()
{
    return this->isRunning;
}