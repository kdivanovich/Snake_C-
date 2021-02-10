#include <stdio.h>
#include <iostream>
#include "Game.h"
#define LOG std::cout
#define NL std::endl

Game *game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("SDL Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 608, false);

	// Uniform framerate: 
	const int FPS = 60;

	Uint32 frameStart;					// how long the game has been running for
	int frameTime;

	while (game->running())
	{
		frameStart = SDL_GetTicks();	// how many seconds it's been since we've init'd SDL

		// Stop the game - handle in controls/conditions
		//game->stopRunning();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;		// how long in ms it's been since last update & render


		int currentFrameTime = game->getFrameVal();
		const int frameDelay = currentFrameTime / FPS;	// max time between frames
		
		if (frameDelay > frameTime)					// if there is remaining time to next frame -> add delay until it's time
		{
			SDL_Delay(14*(frameDelay - frameTime));	// set the game speed here
		}
	}

	game->clean();

	return 0;
}