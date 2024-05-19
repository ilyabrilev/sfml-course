#pragma once

#include <map>
#include <string>
#include <sstream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	sf::RenderWindow* window;

	Player* player;
	//player gui
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//System
	unsigned points;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//World
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;


	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemies();
	void initGui();
	void initWorld();
	void initSystem();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGui();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateWorld();
	void updateCollision();
	void update();

	void renderGui();
	void renderWorld();
	void render();
};

