#include "Game.hpp"


int main(int argc, char* argv[])
{
    Game* game = new Game(900, 600);

    const uint8_t FPS = 60;
    const uint16_t frameDelay = 1000 / FPS;

    uint32_t frameStart = 0;
    uint32_t frameTime = 0;

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->~Game();

    return EXIT_SUCCESS;
}