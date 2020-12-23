#include "Background.h"

Background::Background(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, WIDTH, HEIGHT, game)
{

}

Background::Background(string filename, float x, float y, float vx, Game* game)
	: Actor(filename, x, y, WIDTH, HEIGHT, game) {

	this->vx = vx;
	
	if (vx != 0)
	{
		backgroundAux = new Background(filename, x + WIDTH, y, game);
	}
}

void Background::update()
{
	if (vx != 0)
	{
		x = x + vx;

		if (x + width / 2 < 0)
		{
			x = WIDTH + width / 2;
		}
		if (x - width / 2 > WIDTH)
		{
			x = 0 - width / 2;
		}
	}
}

void Background::draw()
{
	Actor::draw();

	if (backgroundAux != NULL)
	{
		if (x - width / 2 > 0)
		{
			backgroundAux->x = x - width;
		}
		if (x + width / 2 < WIDTH)
		{
			backgroundAux->x = x + width;
		}

		backgroundAux->draw();
	}
}