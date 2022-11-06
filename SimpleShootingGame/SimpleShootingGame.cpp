// SimpleShootingGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

int main()
{

	srand(static_cast<float>(time(0)));

	Game game;
	
	game.run();
	
	  


	return 0;
}

