#include "Enemy.h"

void Enemy::initShape(float pos_x, float pos_y)
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 10 + 3);
	this->shape.setPosition(pos_x, pos_y);
}

void Enemy::initVariables()
{
	this->type = 0;
	this->hpMax = 10;
	this->hp = 0;
	this->damage = 1;
	this->points = 5;
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
