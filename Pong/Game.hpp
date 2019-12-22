#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Client.cpp"


class Game
{
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isRunning = false;

    Ball* ball = nullptr;
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    Client* Client_player2 = nullptr;

    const uint16_t width = 0;
    const uint16_t height = 0;

public:
    Game(const uint16_t width, const uint16_t height);
    ~Game();
    void connectToPlayer();
    void loadBall();
    void loadPlayers();
    void handleEvents();
    void update();
    void render();
    bool running();
};