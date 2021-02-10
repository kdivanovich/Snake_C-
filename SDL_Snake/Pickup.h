#pragma once
#include "Game.h"

class Pickup
{
public:
	Pickup(const char* textureSheet, int x, int y);
	~Pickup();

	void Update();
	void Render();

	int getX() const { return xpos; }
	int getY() const { return ypos; }

	void setX(int x) { xpos = x; }
	void setY(int y) { ypos = y; }

private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};