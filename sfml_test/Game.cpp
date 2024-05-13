#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 500;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Project 1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

//Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

//Destructor
Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions 

void Game::spawnEnemy()
{
	/*
	* spawns enemies and sets their color and positions
	* - set random position
	* - set random color
	* - push into vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>((this->window->getSize().x - this->enemy.getSize().x))),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);
	this->enemies.push_back(this->enemy);
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::updateEnemies()
{
	/*
	* Updates the enemy spawn timer and spawns enemies
	* moves them downwards.
	* removes enemies at the edge of the screen
	*/

	//updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn and reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	//moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 5.f);

		//check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;

				//Gain points
				this->points += 10.f;
			}
		}

		//check if passed the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y) 
		{
			deleted = true;
		}

		//delete the enemy
		if (deleted) {
			this->enemies.erase(this->enemies.begin() + i);
		}		
	}
}

//Event polling
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
	}
}

//Store mouse position relative to window
void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

//Update game logic
void Game::update()
{
	this->pollEvents();
	this->updateMousePositions();
	this->updateEnemies();
}

//Draw on screen
void Game::render()
{
	this->window->clear();

	this->renderEnemies();

	//draw game here
	this->window->display();
}
