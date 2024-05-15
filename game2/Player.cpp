#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->points = 0;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();	
}

Player::~Player()
{
}

sf::RectangleShape Player::getShape() const
{
	return this->shape;
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBounceCollision(const sf::RenderTarget* target)
{
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();
	float top = playerBounds.top;
	float left = playerBounds.left;
	//Left
	if (playerBounds.left <= 0.f)
	{
		left = 0.f;
	}
	//Right
	else if (playerBounds.left + playerBounds.width >= target->getSize().x)
	{
		left = target->getSize().x - playerBounds.width;
	}
	//Top
	if (playerBounds.top <= 0.f)
	{
		top = 0.f;
	}
	//Bottom
	else if (playerBounds.top + playerBounds.height>= target->getSize().y)
	{
		top = target->getSize().y - playerBounds.height;
	}
	this->shape.setPosition(left, top);
}

void Player::update(const sf::RenderTarget* target)
{	
	//keyboard input
	updateInput();

	//window bounds collision
	this->updateWindowBounceCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
