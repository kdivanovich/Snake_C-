#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() const { return isRunning; };

	void stopRunning() { isRunning = false; }

	static SDL_Renderer* renderer;

	bool alive = true;
	bool generateNewPickup = false;
	int score = 0;
	bool goodRandom = false;


	int getFrameVal()	{ return currFrameTime;	}
	int getScore() { return score; }


	void UpdateWindowTitle();
	   	 
private:
	int count = 0;
	bool isRunning = false;
	SDL_Window* window;

	 int currFrameTime ;
};