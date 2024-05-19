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

	int hp;
	int hpMax;

	//private functions
	void initTexture();
	void initSprite();
	void initVariables();

public:
	Player();
	virtual ~Player();

	//modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int getHp() const;
	const int getHpMax() const;

	//Functions 
	void move(const float dirX, const float dirY);
	void updateAttack();
	bool canAttack();

	void update();
	void render(sf::RenderTarget& target);
};

