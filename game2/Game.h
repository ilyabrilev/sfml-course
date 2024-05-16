#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "SwagBall.h"

namespace Game2
{

	class Game
	{
	private:
		sf::VideoMode videoMode;
		sf::RenderWindow* window;
		bool endGame;
		sf::Event sfmlEvent;

		Player player;
		int points;

		sf::Font font;
		sf::Text guiText;
		sf::Text endGameText;

		std::vector<SwagBall> swagBalls;
		float spawnTimerMax;
		float spawnTimer;
		int maxSwagBalls;

		void initVariables();
		void initWindow();
		void initFonts();
		void initText();

	public:
		Game();
		~Game();

		// Accessors
		const bool running() const;
		const bool& getEndGame() const;

		// Modifiers

		// #Functions

		//Core
		void pollEvents();
		void update();
		void render();

		//Game logic
		void updateGui();
		void updatePlayer();
		void renderGui(sf::RenderTarget* target);
		void spawnSwagBalls();
		const int randomizeBallType() const;
		void updateCollision();
	};

}