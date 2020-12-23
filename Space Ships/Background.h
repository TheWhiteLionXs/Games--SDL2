#pragma once

#include "Actor.h"

class Background : public Actor
{
public:
	Background(string filename, float x, float y, Game* game);
	
	Background(string filename, float x, float y, float vx, Game* game);
	void draw() override;
	void update();
	Background* backgroundAux = nullptr;
};