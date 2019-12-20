#include <iostream>

#include <SDL.h>
#include <SDL_net.h>

#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"


Game::Game(const uint16_t width, const uint16_t height) : width(width), height(height)
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
    std::cerr << "SDL Renderer has been initialized" << std::endl;

    this->isRunning = true;

    /* Create Game Objects */
    this->loadBall();
    this->loadPlayers();

    if ((this->player1 && this->player2 && this->ball) == false)
    {
        std::cerr << "Failed to load textures" << std::endl;
        throw EXIT_FAILURE;
    }
    std::cerr << "Textures have been loaded" << std::endl;
}

Game::~Game()
{
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    //SDLNet_Quit();

    std::cerr << "Exiting..." << std::endl;
}

void Game::loadBall()
{
    this->ball = new Ball("../Assets/Ball.png",
        this->renderer,
        12, 11, 6, 6
    );
}

void Game::loadPlayers()
{
    this->player1 = new Player("../Assets/Pong_Stick.png",
        this->renderer,
        13, 7, 3, 18,
        20
    );

    this->player2 = new Player("../Assets/Pong_Stick.png",
        this->renderer,
        13, 7, 3, 18,
        this->width - 30
    );
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
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP)
            {
                uint16_t temp = player1->y - 15;
                if (temp > 20)
                    player1->y = temp;
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                uint16_t temp = player1->y + 15;
                if (temp < this->height - 80)
                    player1->y = temp;
            }
            break;
        default:
            break;
    }
}

void Game::update()
{
    this->player1->update();
    this->player2->update();
    this->ball->update();
}

void Game::render()
{
    SDL_RenderClear(this->renderer);

    /* Add objects to render */
    this->player1->render();
    this->player2->render();
    this->ball->render();

    SDL_RenderPresent(this->renderer);
}

bool Game::running()
{
    return this->isRunning;
}