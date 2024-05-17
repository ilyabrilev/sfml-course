#pragma once

#include <map>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	sf::RenderWindow* window;

	Player* player;

	//Enemies
	Enemy* enemy;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;


	void initWindow();
	void initTextures();
	void initPlayer();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void update();
	void render();
};

