#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy
{
private:
	sf::CircleShape shape;

	int type;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initShape(float pos_x, float pos_y);
	void initVariables();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	void update();
	void render(sf::RenderTarget* target);
};

