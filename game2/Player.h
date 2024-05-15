#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	sf::RectangleShape shape;	

	void initVariables();
	void initShape();

	float movementSpeed;
	int hp;
	int hpMax;
	int points;
public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();	

	sf::RectangleShape getShape() const;

	void updateInput();
	void updateWindowBounceCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

