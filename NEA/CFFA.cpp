//Imported Libraries 
#include "Precomp.h"
#include "Game.h"

int main()
{

	srand(static_cast<unsigned>(time(0)));

	//Init Game engine 
	Game game;
	{
		//Game Loop
		while (game.running())
		{
			//Update
			game.update();

			//Render
			game.render();

		}
	}

	return 0;
}