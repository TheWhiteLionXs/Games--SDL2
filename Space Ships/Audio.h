#pragma once

#include <iostream>
#include <string.h>

using namespace std;

#include <SDL.h>
#include <SDL_mixer.h>

class Audio
{
public:
	Audio(string filename, bool loop);
	~Audio();
	void play();
	bool loop;
	Mix_Music* mix;
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
};

