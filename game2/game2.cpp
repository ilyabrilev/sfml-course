#include <ctime>

#include "Game.h"

int main()
{
    // Init seed
    srand(static_cast<unsigned>(time(0)));

    //init game object
    Game game;

    //Game loop    
    while (game.running())
    {
        game.update();
        game.render();
    }    

    return 0;
}

