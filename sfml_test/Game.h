#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
* Class that acts as a game engine
* wrapper class
*/
class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//private functions 
	void initVariables();
	void initWindow();
	void initEnemies();

public: 
	//constructors / destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void spawnEnemy();
	void renderEnemies();
	void updateEnemies();

	void pollEvents();
	void updateMousePositions();
	void update();
	void render();
};

