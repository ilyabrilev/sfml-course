#include "Player.h"

void Player::initSprite()
{
	//Load from file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE Could not load a texture" << std::endl;
	}

	//set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//resize the sprite
	this->sprite.scale(0.1f, 0.1f);
}

void Player::initVariables()
{
	this->movementSpeed = 3.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 20;
	this->hp = this->hpMax;
}

void Player::initPosition(sf::Vector2u windowSize)
{
	this->setPosition(0.f, windowSize.y - this->getBounds().height);
	
}

Player::Player(sf::Vector2u windowSize)
{
	this->initVariables();
	this->initSprite();
	this->initPosition(windowSize);
}

Player::~Player()
{

}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}

#pragma region Accessors
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();;
}

const int Player::isAlive() const
{
	return this->hp > 0;
}

const int Player::getHp() const
{
	return this->hp;
}

const int Player::getHpMax() const
{
	return this->hpMax;
}
#pragma endregion

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

//Functions
void Player::update(sf::Vector2u windowSize)
{
	this->updateMovement();
	this->updateAttack();
	this->updateCollision(windowSize);
}

void Player::updateMovement()
{
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->move(0.f, 1.f);
	}
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::updateCollision(sf::Vector2u windowSize)
{
	const sf::FloatRect bounds = this->getBounds();
	float left = bounds.left;
	float top = bounds.top;
	//left collision
	if (left < 0.f)
	{
		left = 0.f;
	}
	else if (left + bounds.width >= windowSize.x)
	{
		//right world collision
		left = windowSize.x - bounds.width;
	}

	//top collision
	if (bounds.top < 0.f)
	{
		top = 0.f;
	}
	else if (bounds.top + bounds.height >= windowSize.y)
	{
		//Bottom world collision
		top = windowSize.y - bounds.height;
	}

	//set new position
	if (left != bounds.left || top != bounds.top)
	{
		this->setPosition(left, top);
	}
}

void Player::render(sf::RenderTarget* target) const
{
	target->draw(this->sprite);
}
