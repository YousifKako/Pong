#include <iostream>

#include <SDL.h>
#include <SDL_net.h>


const int port = 8231;


class Server
{
private:
    IPaddress ip = { };
    UDPsocket server = nullptr;

public:
    Server()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            std::cerr << "SDL was unable to be initialized ERR: " << SDL_GetError() << std::endl;
            throw EXIT_FAILURE;
        }

        if (SDLNet_Init() < 0)
        {
            std::cerr << "SDL_Net was unable to be initialized ERR: " << SDLNet_GetError() << std::endl;
            throw EXIT_FAILURE;
        }
    }

    ~Server()
    {
        SDLNet_Quit();
        SDL_Quit();
    }
};

int main(int argc, char* argv[])
{
    Server();
    return EXIT_SUCCESS;
}