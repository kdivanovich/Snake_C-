#include "Game.h"
#include <iostream>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Pickup.h"
#include "Map.h"
#include <time.h> 
#include <string>

#define LOG std::cout
#define NL std::endl

GameObject* head;
GameObject* bodyOne;

Pickup* pickup;

std::vector<GameObject*> bodyParts;

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		LOG << "Subsystems initilised." << NL;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			LOG << "Window created." << NL;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			LOG << "Renderer created." << NL;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	bodyOne = new GameObject("assets/body.png", 2 * 32, 32);
	head = new GameObject("assets/player.png", 2 * 32, 2 * 32);

	std::srand(time(0));
	int randX = std::rand() % 23 + 1;		// generate random numbers between the borders
	int randY = std::rand() % 17 + 1;
	pickup = new Pickup("assets/pickup.png", randX * 32, randY * 32);

	bodyParts.push_back(bodyOne);
	bodyParts.push_back(head);

	map = new Map();

	currFrameTime = 1000;

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);


	// Keyboard controls	
	while (SDL_PollEvent(&event) != 0)
	{
		// to quit:
		if (event.type == SDL_QUIT)
			isRunning = false;
		// key press:
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				if (head->getIsGoingHorizontal() == true)
				{
					head->setIsGoingHorizontal(false);
					head->setYdir(-1);
				}
				break;
			case SDLK_DOWN:
				if (head->getIsGoingHorizontal() == true)
				{
					head->setIsGoingHorizontal(false);
					head->setYdir(1);
				}
				break;
			case SDLK_LEFT:
				if (head->getIsGoingHorizontal() == false)
				{
					head->setIsGoingHorizontal(true);
					head->setXdir(-1);
				}
				break;
			case SDLK_RIGHT:
				if (head->getIsGoingHorizontal() == false)
				{
					head->setIsGoingHorizontal(true);
					head->setXdir(1);
				}
				break;
			default:
				break;
			}
		}
	}
}

void Game::update()
{
	if (!alive)
		return;

	int snakeElemsIterator = bodyParts.size() - 1;

	for (int i = 0; i < snakeElemsIterator; ++i)				// i = 0,1,2
	{
		bodyParts[i]->UpdateFollow(bodyParts[i + 1]->getX(), bodyParts[i + 1]->getY());

		if (bodyParts[i + 1]->getIsGoingHorizontal())				// if going  *horizontal*
		{
			if (bodyParts[i + 1]->getXdir() > 0)					// if going  left -> right
			{
				if (bodyParts[i]->getY() == bodyParts[i + 1]->getY())
				{
					bodyParts[i]->setXdir(1);
				}
			}
			else												// if going  right -> left
			{
				if (bodyParts[i]->getY() == bodyParts[i + 1]->getY())
				{
					bodyParts[i]->setXdir(-1);
				}
			}
			bodyParts[i]->setIsGoingHorizontal(true);
		}
		else													// if going  *vertical*
		{
			if (bodyParts[i + 1]->getYdir() > 0)					// if going  top -> down
			{
				if (bodyParts[i]->getX() == bodyParts[i + 1]->getX())
				{
					bodyParts[i]->setYdir(1);
				}
			}
			else												// if going down -> top
			{
				if (bodyParts[i]->getX() == bodyParts[i + 1]->getX())
				{
					bodyParts[i]->setYdir(-1);
				}
			}
			bodyParts[i]->setIsGoingHorizontal(false);
		}
	}
	head->Update();



	if (head->getX() == pickup->getX() && head->getY() == pickup->getY())
	{
		LOG << "Pickup taken" << NL;
		score++;														// score up
		currFrameTime -= 50;											// speed up	
		generateNewPickup = true;

		if (bodyParts[0]->getIsGoingHorizontal())						// if going  *horizontal*
		{
			if (bodyParts[0]->getXdir() < 0)							// if going  right -> left
			{
				bodyParts.insert(bodyParts.begin(),
					new GameObject("assets/body.png", bodyParts[0]->getX() + 32, bodyParts[0]->getY()));
				bodyParts[0]->setIsGoingHorizontal(bodyParts[1]->getIsGoingHorizontal());
			}
			else														// if going  left -> right
			{
				bodyParts.insert(bodyParts.begin(),
					new GameObject("assets/body.png", bodyParts[0]->getX() - 32, bodyParts[0]->getY()));
				bodyParts[0]->setIsGoingHorizontal(bodyParts[1]->getIsGoingHorizontal());
			}
		}
		if (!bodyParts[0]->getIsGoingHorizontal())						// if going  *vertical*
		{
			if (bodyParts[0]->getYdir() > 0)							// if going  top -> down		
			{
				bodyParts.insert(bodyParts.begin(),
					new GameObject("assets/body.png", bodyParts[0]->getX(), bodyParts[0]->getY() - 32));
				bodyParts[0]->setIsGoingHorizontal(bodyParts[1]->getIsGoingHorizontal());
			}
			else														// if going  down -> top	
			{
				bodyParts.insert(bodyParts.begin(),
					new GameObject("assets/body.png", bodyParts[0]->getX(), bodyParts[0]->getY() + 32));
				bodyParts[0]->setIsGoingHorizontal(bodyParts[1]->getIsGoingHorizontal());
			}
		}
		bodyParts[0]->setXdir(bodyParts[1]->getXdir());
		bodyParts[0]->setYdir(bodyParts[1]->getYdir());
	}


	// Generate a pickup on a square not occupied by the snake's body
	if (generateNewPickup)
	{
		std::srand(time(0));

		int randX;
		int randY;

		while (goodRandom == false)
		{
			randX = std::rand() % 23 + 1;
			randY = std::rand() % 17 + 1;

			for (int i = 0; i < bodyParts.size(); ++i)
			{
				int bodyX = bodyParts[i]->getX() / 32;
				int bodyY = bodyParts[i]->getY() / 32;

				if (bodyX == randX && bodyY == randY)
				{
					goodRandom = false;
					break;
				}
				goodRandom = true;
			}
		}

		if (goodRandom == true)
		{
			pickup->setX(randX * 32);
			pickup->setY(randY * 32);
			generateNewPickup = false;
			goodRandom = false;
		}
	}

	pickup->Update();
	   
	// check if next square is body i.e. end game
	for (int i = 0; i < snakeElemsIterator; ++i)
	{
		if (head->getX() == bodyParts[i]->getX() && head->getY() == bodyParts[i]->getY())
			alive = false;
	}

	// check if snake hit the border
	if (head->getX() / 32 == 0 || head->getX() / 32 == 24 ||
		head->getY() / 32 == 0 || head->getY() / 32 == 18 )
	{
		alive = false;
	}


	// Timer
	unsigned int lastTime = 0, currentTime;
	std::string timeElapsed;
	std::string secondsStr;
	std::string minutesStr;

	if (alive) {
		currentTime = SDL_GetTicks();					// Better idea: use std::clock
														// because this is dependent on the ticks
		unsigned int milliseconds = currentTime % 1000;	// meaning at game over the timer is dead too
		currentTime /= 1000;
		unsigned int seconds = currentTime % 60;
		currentTime /= 60;
		unsigned int minutes = currentTime % 60;

		secondsStr = std::to_string(seconds);
		minutesStr = std::to_string(minutes);
	}

	// Score
	std::string title = "SDL Snake | Score: " + std::to_string(getScore()) + 
		" | Time: " + minutesStr + ":" + secondsStr;
	

	SDL_SetWindowTitle(window, title.c_str());
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	pickup->Render();

	int snakeElemsIterator = bodyParts.size() - 1;
	for (int i = 0; i < snakeElemsIterator; ++i)
	{
		bodyParts[i]->Render();
	}

	head->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	LOG << "Game cleaned." << NL;
}

