#include "Game.hpp"


int main(int argc, char* argv[])
{
    Game* game = new Game();

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->~Game();

    return EXIT_SUCCESS;
}