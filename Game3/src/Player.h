#pragma once
#include <iostream>
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Bullet.h"
#include "BulletsContainer.h"
#include "Globals.h"

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	sf::Texture mainBulletTexture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//inits
	void initSprite();
	void initVariables();
	void initPosition(sf::Vector2u windowSize);

public:
	Player(sf::Vector2u windowSize);
	virtual ~Player();

	//modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void loseHp(const int value);

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int getHp() const;
	const int getHpMax() const;
	const int isAlive() const;
	bool canAttack();

	//Functions 
	void move(const float dirX, const float dirY);

	void update(sf::Vector2u windowSize);
	void updateMovement();
	void updateAttack(BulletsContainer &playerBullets);
	void updateCollision(sf::Vector2u windowSize);
	void render(sf::RenderTarget* target) const;
};

