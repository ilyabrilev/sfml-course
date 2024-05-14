#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
	this->endGame = false;
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

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Jacquard12-Regular.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS Failed to load font" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("None");
}

//Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
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

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n" << "Health: " << this->health;

	this->uiText.setString(ss.str());
}

const bool Game::getEndGame() const
{
	return this->endGame;
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

	//Randomize enemy time
	int type = rand() % 5;
	 
	// ugh
	switch (type)
	{
	case 0:
		this->enemy.setFillColor(sf::Color::Magenta);
		this->enemy.setSize(sf::Vector2f(20.f, 20.f));
		break;
	case 1:
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		break;
	case 2:
		this->enemy.setFillColor(sf::Color::Cyan);
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		break;
	case 3:
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		break;
	case 4:
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		break;
	default:
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		break;
	}

	this->enemies.push_back(this->enemy);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
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

		//check if passed the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}

	//check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;

			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
					{
						this->points += 10;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
					{
						this->points += 7;
					}
					else //and so on
					{
						this->points += 1;
					}
					

					//delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else 
	{
		this->mouseHeld = false;
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

	if (!this->endGame) {
		this->updateMousePositions();
		this->updateEnemies();
		this->updateText();
	}

	//endgame condition
	if (this->health <= 0) {
		this->endGame = true;
	}
}

//Draw on screen
void Game::render()
{
	this->window->clear();

	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	//draw game here
	this->window->display();
}
