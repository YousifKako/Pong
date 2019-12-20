#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_net.h>


const int port = 8231;


class Game
{
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isRunning = false;

    uint16_t width = 900;
    uint16_t height = 600;

    IPaddress ip = { };
    TCPsocket server = nullptr;

public:
    Game();
    ~Game();
    void handleEvents();
    void update();
    void render();
    bool running();
};