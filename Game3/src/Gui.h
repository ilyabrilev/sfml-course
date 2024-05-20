#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.h"

class Gui
{
private:

	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	void initGui(sf::RenderWindow* window);
public:
	Gui(sf::RenderWindow* window);
	virtual ~Gui();

	void update(int points, Player* player);
	void render(sf::RenderTarget* target);
	void renderGameOver(sf::RenderTarget* target);
};

