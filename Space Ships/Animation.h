#pragma once

#include "Game.h"

class Animation
{
public:
	Animation(string filename, float actorWidth, float actorHeight, float fileWidth, float fileHeight, int updateFrecuence, int totalFrames, Game* game);
	bool update();
	void draw(float x, float y);
	int actorWidth;
	int actorHeight;
	int fileWidth;
	int fileHeight;
	int currentFrame;
	int totalFrames;
	Game* game;

	SDL_Texture* texture;
	SDL_Rect source;
	float frameWidth;
	float frameHeight;
	int updateFrecuence = 0;
	int updateTime = 0;
};

