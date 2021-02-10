#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void UpdateFollow(int newX, int newY);
	void Render();

	int getX() const { return xpos; }
	int getY() const { return ypos; }
	void setX(int newX) { xpos = newX; }
	void setY(int newY) { ypos = newY; }

	int getXdir() const { return xdir; }
	int getYdir() const { return ydir; }
	void setXdir(int newXdir) { xdir = newXdir; }
	void setYdir(int newYdir) { ydir = newYdir; }

	bool getIsGoingHorizontal() const { return isGoingHorizontal; }
	void setIsGoingHorizontal(bool flag) { isGoingHorizontal = flag; }

private:
	int xpos, ypos;
	int xdir;
	int ydir;

	bool isGoingHorizontal;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};