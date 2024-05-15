#include "SwagBall.h"

void SwagBall::initShape(const sf::RenderWindow* window)
{
	int radius = rand() % 10 + 10;
	this->shape.setRadius(static_cast<float>(radius));
	sf::Color color(rand()%255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	this->shape.setFillColor(color);

	this->shape.setPosition(sf::Vector2f(
		static_cast<float>(rand()%(window->getSize().x - radius * 2)),
		static_cast<float>(rand()%(window->getSize().y - radius * 2))
	));
}

SwagBall::SwagBall(const sf::RenderWindow* window)
{
	this->initShape(window);
}

SwagBall::~SwagBall()
{

}

const sf::CircleShape SwagBall::getShape() const
{
	return this->shape;
}

void SwagBall::update()
{
}

void SwagBall::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
