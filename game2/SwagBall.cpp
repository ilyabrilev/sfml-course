#include "SwagBall.h"

namespace Game2
{
	void SwagBall::initShape(const sf::RenderWindow* window)
	{
		int radius = rand() % 10 + 10;
		this->shape.setRadius(static_cast<float>(radius));

		sf::Color color;
		switch (this->type) 
		{
		case SwagBallTypes::DEFAULT:
			color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
			break;
		case SwagBallTypes::DAMAGING:
			color = sf::Color::Red;
			this->shape.setOutlineColor(sf::Color::White);
			this->shape.setOutlineThickness(2.f);
			break;
		case SwagBallTypes::HEALING:
			color = sf::Color::Green;
			this->shape.setOutlineColor(sf::Color::White);
			this->shape.setOutlineThickness(2.f);
			break;
		}

		this->shape.setFillColor(color);

		this->shape.setPosition(sf::Vector2f(
			static_cast<float>(rand() % (window->getSize().x - radius * 2)),
			static_cast<float>(rand() % (window->getSize().y - radius * 2))
		));
	}

	SwagBall::SwagBall(const sf::RenderWindow* window, int type)
		: type(type)
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

	const int& SwagBall::getType() const
	{
		return this->type;
	}

	void SwagBall::update()
	{
	}

	void SwagBall::render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
	}
}
