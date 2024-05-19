#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initTextures();
	this->initEnemies();
	this->initGui();
	this->initWorld();
	this->initSystem();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game3", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = spawnTimerMax;
}

void Game::initGui()
{
	// load font
	if (!this->font.loadFromFile("Fonts/PoetsenOne-Regular.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << std::endl;
	}

	// init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");
	this->pointText.setPosition(static_cast<float>(this->window->getSize().x - 150), 25.f);


	//init player gui
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
	this->playerHpBarBack.setPosition(sf::Vector2f(20.f, 20.f));

	// init game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game over");
	this->gameOverText.setPosition(sf::Vector2f(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f)
	);
}

void Game::initWorld()
{
	if (!this->worldBackgroundTexture.loadFromFile("Textures/background1.jpg"))
	{
		std::cout << "ERROR::GAME:: Could not load background" << std::endl;
	}
	this->worldBackground.setTexture(this->worldBackgroundTexture);
}

void Game::initSystem()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

//Functions
void Game::updateEnemies()
{
	//spawn
	this->spawnTimer += 1.f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % (this->window->getSize().x - 20), -100.f));
		this->spawnTimer = 0.f;
	}

	//Update (remove at the bottom)
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* enemy = this->enemies[i];

		enemy->update();

		//enemy removed from the top
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//delete an enemy
			delete enemy;
			this->enemies.erase(this->enemies.begin() + i);
		}
		//enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			//delete enemy if it toches a player
			this->player->loseHp(enemy->getDamage());
			delete enemy;
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::updateCombat()
{
	//update collision between bullets and enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool enemy_removed = false;
		this->enemies[i]->update();

		for (int j = 0; j < this->bullets.size() && !enemy_removed; j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}
	}
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	const sf::FloatRect bounds = this->player->getBounds();
	const sf::Vector2u windowSize = this->window->getSize();
	float left = bounds.left;
	float top = bounds.top;
	//left collision
	if (left < 0.f)
	{
		left = 0.f;
	}
	else if (left + bounds.width >= windowSize.x)
	{
		//right world collision
		left = windowSize.x - bounds.width;
	}

	//top collision
	if (bounds.top < 0.f)
	{
		top = 0.f;
	}
	else if (bounds.top + bounds.height >= windowSize.y)
	{
		//Bottom world collision
		top = windowSize.y - bounds.height;
	}

	//set new position
	if (left != bounds.left || top != bounds.top)
	{
		this->player->setPosition(left, top);
	}
}

void Game::update()
{
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGui();
	this->updateWorld();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0) {
			this->update();
		}
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y,
				0.f,
				-1.f,
				5.f
			));
	}
}

void Game::updateGui()
{
	//points gui
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());

	//update player gui	
	float hpPersent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(this->playerHpBarBack.getSize().x * hpPersent, this->playerHpBar.getSize().y));
}

void Game::updateBullets()
{
	for (int i = 0; i < this->bullets.size(); i++)
	{
		Bullet* bullet = this->bullets[i];

		bullet->update();

		//bullet culling top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//delete a bullet 
			delete bullet;
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Game::render()
{
	this->window->clear();

	//render stuff
	// 
	//Draw world
	this->renderWorld();

	this->player->render(*this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->renderGui();

	//game over screen
	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

void Game::renderGui()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}
