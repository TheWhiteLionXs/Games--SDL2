#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	init();
}

void GameLayer::init()
{
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	points = 0;
	textPoints = new Text("0", WIDTH * 0.92, HEIGHT * 0.05, game);

	player = new Player(50, 50, game);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);

	projectiles.clear();

	enemies.clear();
	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new Enemy(300, 200, game));
}

void GameLayer::processControls()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		keysToControls(event);
	}
	if (controlShoot)
	{
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL)
		{
			projectiles.push_back(newProjectile);
		}
	}
	// Eje X
	if (controlMoveX > 0)
	{
		player->moveX(1);
	}
	else if (controlMoveX < 0)
	{
		player->moveX(-1);
	}
	else
	{
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0)
	{
		player->moveY(1);
	}
	else if (controlMoveY < 0)
	{
		player->moveY(-1);
	}
	else
	{
		player->moveY(0);
	}
}

void GameLayer::keysToControls(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		int code = event.key.keysym.sym;

		switch (code)
		{
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_F11:
			game->scale();
			break;
		case SDLK_d:
			controlMoveX = 1;
			break;
		case SDLK_a:
			controlMoveX = -1;
			break;
		case SDLK_w:
			controlMoveY = -1;
			break;
		case SDLK_s:
			controlMoveY = 1;
			break;
		case SDLK_SPACE:
			controlShoot = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP)
	{
		int code = event.key.keysym.sym;

		switch (code)
		{
		case SDLK_d:
			if (controlMoveX == 1)
			{
				controlMoveX = 0;
			}
			break;
		case SDLK_a:
			if (controlMoveX == -1)
			{
				controlMoveX = 0;
			}
			break;
		case SDLK_w:
			if (controlMoveY == -1)
			{
				controlMoveY = 0;
			}
			break;
		case SDLK_s:
			if (controlMoveY == 1)
			{
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE:
			controlShoot = false;
			break;
		}
	}
}

void GameLayer::update()
{
	//projectiles.push_back(new Projectile(player->x, player->y, game));

	background->update();

	// Generar Enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0)
	{
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (3600 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY, game));
		newEnemyTime = 10;
	}

	player->update();
	for (auto const& enemy : enemies)
	{
		enemy->update();
	}

	for (auto const& projectile : projectiles)
	{
		projectile->update();
	}

	for (auto const& enemy : enemies)
	{
		if (player->isOverlap(enemy))
		{
			init();
			return;
		}
	}

	//Colisiones, Enemy - Projectile
	
	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;

	for (auto const& projectile : projectiles)
	{
		if (projectile->isInRender() == false)
		{
			bool pInList = std::find(deleteProjectiles.begin(), deleteProjectiles.end(), projectile) != deleteProjectiles.end();

			if (!pInList)
			{
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : enemies)
	{
		for (auto const& projectile : projectiles)
		{
			if (enemy->isOverlap(projectile))
			{
				bool pInList = std::find(deleteProjectiles.begin(), deleteProjectiles.end(), projectile) != deleteProjectiles.end();

				if (!pInList)
				{
					deleteProjectiles.push_back(projectile);
				}

				bool enInList = std::find(deleteEnemies.begin(), deleteEnemies.end(), enemy) != deleteEnemies.end();

				if (!enInList)
				{
					deleteEnemies.push_back(enemy);
				}
				points++;
				textPoints->content = to_string(points);
			}
		}
	}
	for (auto const& delEnemy : deleteEnemies)
	{
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles)
	{
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	
	deleteProjectiles.clear();
	
	for (auto const& enemy : enemies)
	{
		for (auto const& projectile : projectiles)
		{
			if (enemy->isOverlap(projectile))
			{

			}
		}
	}
}

void GameLayer::draw()
{
	background->draw();

	for (auto const& projectile : projectiles)
	{
		projectile->draw();
	}

	player->draw();

	for (auto const& enemy : enemies)
	{
		enemy->draw();
	}

	textPoints->draw();
	backgroundPoints->draw();

	SDL_RenderPresent(game->renderer); //Renderiza
}