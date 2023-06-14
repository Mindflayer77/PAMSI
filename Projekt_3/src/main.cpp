#include "../inc/Game.h"



int main()
{
    Game game(4);
    game.init(title,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, fullscreen);
    while(game.isRunning())
    {
        game.handleEvents();
        game.update();
    }
}