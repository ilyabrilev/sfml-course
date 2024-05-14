#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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

	//resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//private functions 
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();

public: 
	//constructors / destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void renderEnemies(sf::RenderTarget& target);
	void updateEnemies();
	void renderText(sf::RenderTarget& target);
	void updateText();

	void pollEvents();
	void updateMousePositions();
	void update();
	void render();
};

