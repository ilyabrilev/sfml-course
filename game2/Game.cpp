#include "Game.h"


namespace Game2
{
	Game::Game()
	{
		this->initVariables();
		this->initWindow();
		this->initFonts();
		this->initText();
	}

	Game::~Game()
	{
		delete this->window;
	}

#pragma region Inits
	void Game::initVariables()
	{
		this->endGame = false;

		this->spawnTimerMax = 30.f;
		this->spawnTimer = this->spawnTimerMax;
		this->maxSwagBalls = 10;

		this->points = 0;
	}

	void Game::initWindow()
	{
		this->videoMode = sf::VideoMode(800, 600);
		this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
		this->window->setFramerateLimit(60);
	}

	void Game::initFonts()
	{
		if (!this->font.loadFromFile("Fonts/PoetsenOne-Regular.ttf"))
		{
			std::cout << "!!! ERROR::GAME::INITFONTS Failed to load PoetsenOne-Regular" << std::endl;
		}
	}

	void Game::initText()
	{
		//Gui text
		this->guiText.setFont(this->font);
		this->guiText.setCharacterSize(24);
		this->guiText.setFillColor(sf::Color::White);

		//endgame Text
		this->endGameText.setFont(this->font);
		this->endGameText.setCharacterSize(60);
		this->endGameText.setFillColor(sf::Color::Red);
		this->endGameText.setPosition(sf::Vector2f(300, 250));
		this->endGameText.setString("YOU DIE");
	}
#pragma endregion

	// Accessors
	const bool Game::running() const
	{
		return this->window->isOpen();
	}

	const bool& Game::getEndGame() const
	{
		return this->endGame;
	}

	// Modifiers

	// Functions
#pragma region Core
	void Game::update()
	{
		this->pollEvents();

		if (this->endGame == false) 
		{
			this->spawnSwagBalls();
			this->updatePlayer();
			this->updateCollision();
			this->updateGui();
		} 
	}

	void Game::render()
	{
		//render stuff

		this->window->clear();

		//render player
		this->player.render(this->window);

		//render swag balls
		for (auto i : this->swagBalls)
		{
			i.render(this->window);
		}

		//render gui
		this->renderGui(this->window);

		//Render end text

		if (this->endGame)
		{
			this->window->draw(this->endGameText);
		}

		this->window->display();
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
#pragma endregion

#pragma region Game logic
	void Game::spawnSwagBalls()
	{
		if (this->spawnTimer < this->spawnTimerMax)
		{
			this->spawnTimer += 1.f;
		}
		else {
			if (this->swagBalls.size() < this->maxSwagBalls)
			{
				this->swagBalls.push_back(SwagBall(this->window, this->randomizeBallType()));

				this->spawnTimer = 0.f;
			}
		}
	}

	const int Game::randomizeBallType() const
	{
		int type = SwagBallTypes::DEFAULT;
		int randValue = rand() % 100 + 1;

		if (randValue > 60 && randValue <= 80)
		{
			type = SwagBallTypes::DAMAGING;
		}
		else if (randValue > 80 && randValue <= 100)
		{
			type = SwagBallTypes::HEALING;
		}

		return type;
	}

	void Game::updateCollision()
	{
		// check the collision between the player and balls
		for (int i = 0; i < this->swagBalls.size(); i++)
		{
			if (this->player.getShape().getGlobalBounds().intersects(swagBalls[i].getShape().getGlobalBounds()))
			{
				// Ball Action
				switch (this->swagBalls[i].getType())
				{
				case SwagBallTypes::DEFAULT:
					this->points++;
					break;
				case SwagBallTypes::DAMAGING:
					this->player.takeDamage(10);
					break;
				case SwagBallTypes::HEALING:
					this->player.gainHealth(1);
					break;
				}

				//remove the ball
				this->swagBalls.erase(this->swagBalls.begin() + i);
			}
		}
	}

	void Game::renderGui(sf::RenderTarget* target)
	{
		target->draw(this->guiText);
	}

	void Game::updateGui()
	{
		std::stringstream ss;
		ss << " - Points: " << this->points << "\n"
			<< " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";
		this->guiText.setString(ss.str());
	}

	void Game::updatePlayer()
	{
		this->player.update(this->window);

		if (this->player.getHp() <= 0) 
		{
			this->endGame = true;
		}
	}
#pragma endregion
}