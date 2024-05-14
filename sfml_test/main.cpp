#include <iostream>

#include "Game.h"

int main()
{
    //init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //init game engine
    Game game;

    //Game loop
    while (game.running() && !game.getEndGame())
    {
        //Update
        game.update();

        //Render
        game.render();
    }


    //End of an app
    return 0;
}