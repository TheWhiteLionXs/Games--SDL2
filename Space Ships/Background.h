#pragma once

#include "Actor.h"

class Background : public Actor
{
public:
	Background(string filename, float x, float y, Game* game);
};