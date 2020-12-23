#include "Text.h"

Text::Text(string content, float x, float y, Game* game)
{
	this->content = content;
	this->x = x;
	this->y = y;
	this->game = game;
}

void Text::draw() {
	SDL_Color color;
	color.r = 255; //Red
	color.g = 255; //Green
	color.b = 255; //Blue
	color.a = 255; //Transparency

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, content.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	SDL_Rect rect;
	rect.x = x - surface->w / 2;
	rect.y = y - surface->h / 2;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}