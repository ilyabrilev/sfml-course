#include "Player.h"

void Player::initTexture()
{
	//Load from file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE Could not load a texture" << std::endl;
	}
}

void Player::initSprite()
{
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//resize the sprite
	this->sprite.scale(0.1f, 0.1f);
}

void Player::initVariables()
{
	this->movementSpeed = 1.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
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
void Player::update()
{
	this->updateAttack(); 
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
