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

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;


	void initWindow();
	void initTextures();
	void initWorld();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();
	void updateInput();

	void spawnBullet();

	void updateBullets();
	void updateCombat();
	void update();

	void render();
};

