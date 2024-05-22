#include <iostream>
#include <time.h>

#include "src/Game.h"

int main()
{
	std::cout << std::filesystem::current_path() << std::endl;

	srand(static_cast<unsigned>(time(0)));

	Game game;

	game.run();

	return 0;
}
