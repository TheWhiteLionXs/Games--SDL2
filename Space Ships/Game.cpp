#include "Game.h"
#include "GameLayer.h"

void Game::scale()
{
	scaledToMax = !scaledToMax;

	if (scaledToMax)
	{
		SDL_DisplayMode PCdisplay;
		SDL_GetCurrentDisplayMode(0, &PCdisplay);
		float scaleX = (float)PCdisplay.w / (float)WIDTH;
		float scaleY = (float)PCdisplay.h / (float)HEIGHT;

		scaleLower = scaleX;
		if (scaleY < scaleX)
		{
			scaleLower = scaleY;
		}

		SDL_SetWindowSize(window, WIDTH * scaleLower, HEIGHT * scaleLower);
		SDL_RenderSetScale(renderer, scaleLower, scaleLower);
	}
	else
	{
		scaleLower = 1;
		SDL_SetWindowSize(window, WIDTH, HEIGHT);
		SDL_RenderSetScale(renderer, 1, 1);
	}
}

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Error SDL_Init" << SDL_GetError() << endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0)
	{
		cout << "Error Window y Renderer" << SDL_GetError() << endl;
	}

	SDL_ShowCursor(0);

	SDL_SetWindowTitle(window, "Juego de Naves");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		
	gameLayer = new GameLayer(this);

	//Fonts
	TTF_Init();
	font = TTF_OpenFont("res/sans.ttf", 24);

	loopActive = true; //The loop is active
	loop();
}

SDL_Texture* Game::getTexture(string filename)
{
	if (mapTextures.find(filename) != mapTextures.end())
	{
		cout << "Retorno recurso cacheado" << filename << endl;
	}
	else
	{
		cout << "Nuevo hay que cachearlo" << filename << endl;
		SDL_Surface* surface = IMG_Load(filename.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		mapTextures[filename] = texture;
	}

	return mapTextures[filename];

}

void Game::loop()
{
	int initTick; //Milisegundos al inicio del loop
	int endTick; //Milisegundos al final del loop
	int differenceTick; //Fin - Inicio

	while (loopActive)
	{
		initTick = SDL_GetTicks();

		// Controles
		gameLayer->processControls();
		// Actualizar elementos
		gameLayer->update();
		//Dibujar
		gameLayer->draw();

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		if (differenceTick < (1000 / 30 ))
		{
			SDL_Delay((1000 / 30) - differenceTick);
		}
	}
}