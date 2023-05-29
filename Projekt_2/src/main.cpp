#include "../inc/Game.h"
#include "../inc/Movie.h"
#include "../inc/ReadData.h"
#include "../inc/Sorting.h"
#include "../inc/TextureManager.h"
#include "../inc/Visualization.h"
#include <SDL2/SDL.h>

Game *game = nullptr;

int main()
{
    game = new Game();
    game->init("Sorting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 910, 750, false);
    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->cleanUp();
    return 0;
}