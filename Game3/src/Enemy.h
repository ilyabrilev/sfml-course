#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy
{
private:
	unsigned pointCount;
	sf::CircleShape shape;

	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;
	int radius;

	void initVariables();
	void initShape(float pos_x, float pos_y);

public:
	Enemy(float pos_x, float pos_y);
	Enemy(unsigned xMax);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);
};

