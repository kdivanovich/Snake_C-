#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);

	xpos = x;
	ypos = y;
	xdir = 1; 
	ydir = 1;
	isGoingHorizontal = false;
}

void GameObject::Update()
{
	// move horizontal or vertical
	if (isGoingHorizontal)
		xpos += 32 * xdir;
	else
		ypos += 32 * ydir;

	// make the snake wrap around the screen
	if (xpos >= 800)
		xpos = 0;
	else if (xpos < 0)
		xpos = 24 * 32;
	else if (ypos >= 608)
		ypos = 0;
	else if (ypos < 0)
		ypos = 18 * 32;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::UpdateFollow(int newX, int newY) 
{
	// move horizontal or vertical
	if (isGoingHorizontal)
		xpos += 32 * xdir;
	else
		ypos += 32 * ydir;

	// make the snake wrap around the screen
	if (xpos >= 800)
		xpos = 0;
	else if (xpos < 0)
		xpos = 24 * 32;
	else if (ypos >= 608)
		ypos = 0;
	else if (ypos < 0)
		ypos = 18 * 32;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = newX;
	destRect.y = newY;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}