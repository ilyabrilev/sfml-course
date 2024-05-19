#include "Enemy.h"


void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->hpMax = this->pointCount;
	this->hp = this->hpMax;
	this->damage = 1;
	this->points = this->pointCount;
	this->speed = static_cast<float>(this->pointCount)/4.f;
}

void Enemy::initShape(float pos_x, float pos_y)
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setPosition(pos_x, pos_y);
	this->shape.setFillColor(sf::Color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
