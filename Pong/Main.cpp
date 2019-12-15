#include <iostream>

#include <SDL.h>
#include <SDL_net.h>


const int port = 8231;


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL unable to be initialized ERR: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (SDLNet_Init() < 0)
    {
        std::cerr << "SDL_net unable to be initialized ERR: " << SDLNet_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    IPaddress ip;
    SDLNet_ResolveHost(&ip, NULL, port);

    TCPsocket server = SDLNet_TCP_Open(&ip);

    SDLNet_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}