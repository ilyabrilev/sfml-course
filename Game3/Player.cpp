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
	this->movementSpeed = 3.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 20;
	this->hp = this->hpMax;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
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

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();;
}

const int Player::getHp() const
{
	return this->hp;
}

const int Player::getHpMax() const
{
	return this->hpMax;
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
