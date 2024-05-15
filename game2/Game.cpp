#include "Game.h"


void Game::initVariables()
{
	this->endGame = false;

	this->spawnTimerMax = 5.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}
// Accessors

// Modifiers

// Functions
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::update()
{
	this->pollEvents();
	this->spawnSwagBalls();

	this->player.update(this->window);
	this->updateCollision();
}

void Game::render()
{
	this->window->clear();

	//render stuff
	this->player.render(this->window);

	for (auto i : this->swagBalls)
	{
		i.render(this->window);
	}

	this->window->display();
}

void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 1.f;
	}
	else {
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall(this->window));

			this->spawnTimer = 0.f;
		}		
	}
}

void Game::updateCollision()
{
	// check the collision
	for (int i = 0; i < this->swagBalls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(swagBalls[i].getShape().getGlobalBounds())) 
		{
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::pollEvents()
{	
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape) 
			{
				this->window->close();
			}
			break;
		}
	}	
}