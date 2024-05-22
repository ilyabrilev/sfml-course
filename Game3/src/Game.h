#pragma once

#include <map>
#include <string>
#include <sstream>
#include <functional>

#include "./Player.h"
#include "./Bullet.h"
#include "./Enemy.h"
#include "./Gui.h"
#include "./EnemiesContainer.h"
#include "./BulletsContainer.h"
#include "./Globals.h"

class Game
{
private:
	sf::RenderWindow* window;

	Player* player;

	Gui* gui;

	//System
	unsigned points;

	//Enemies
	EnemiesContainer* enemies;

	//World
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground;

	std::vector<Bullet*> bullets;
	BulletsContainer* c_bullets;

	void initWindow();
	void initWorld();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();

	void updateBullets();
	void updatePlayer();
	void updateCombat();
	void update();

	void render();
};

