#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, Game* game)
{
	this->game = game;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->renderer, surface);
	
	this->x = x;
	this->y = y;

	this->fileWidth = width;
	this->fileHeigth = height;

	this->width = width;
	this->height = height;
}

void Actor::draw()
{
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth;
	source.h = fileHeigth;

	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(game->renderer, texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}

bool Actor::isOverlap(Actor* actor)
{
	bool overlap = false;
	if (actor->x - actor->width / 2 <= x + width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2)
	{
		overlap = true;
	}
	return overlap;
}