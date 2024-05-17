#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	//private functions
	void initTexture();
	void initSprite();
	void initVariables();

public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;

	//Functions 
	void move(const float dirX, const float dirY);
	void updateAttack();
	bool canAttack();

	void update();
	void render(sf::RenderTarget& target);
};

