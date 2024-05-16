#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

namespace Game2
{
	class Player
	{
	private:
		sf::RectangleShape shape;

		void initVariables();
		void initShape();

		float movementSpeed;
		int hp;
		int hpMax;
	public:
		Player(float x = 0.f, float y = 0.f);
		virtual ~Player();

		//Accessors
		sf::RectangleShape getShape() const;
		const int& getHp() const;
		const int& getHpMax() const;

		//Functions
		void updateInput();
		void updateWindowBounceCollision(const sf::RenderTarget* target);
		void update(const sf::RenderTarget* target);
		void render(sf::RenderTarget* target);

		void takeDamage(const int damage);
		void gainHealth(const int health);
	};
}
