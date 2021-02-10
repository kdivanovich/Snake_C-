#include "Pickup.h"
#include "TextureManager.h"

Pickup::Pickup(const char* textureSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);

	xpos = x;
	ypos = y;
}

void Pickup::Update()
{
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Pickup::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}