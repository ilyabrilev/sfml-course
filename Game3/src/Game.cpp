#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->player = new Player(this->window->getSize());
	this->initTextures();
	this->enemies = new EnemiesContainer();
	this->gui = new Gui(this->window);
	this->initWorld();
	this->points = 0;

}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->gui;

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

	delete this->enemies;
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

void Game::initWorld()
{
	if (!this->worldBackgroundTexture.loadFromFile("Textures/background1.jpg"))
	{
		std::cout << "ERROR::GAME:: Could not load background" << std::endl;
	}
	this->worldBackground.setTexture(this->worldBackgroundTexture);
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->isAlive())
		{
			this->update();
		}
		this->render();
	}
}

//update collision between bullets and enemies
void Game::updateCombat()
{
	for (int i = 0; i < this->enemies->size(); i++)
	{
		for (int j = 0; j < this->bullets.size(); j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->enemies->at(i)->getBounds()))
			{
				this->points += this->enemies->at(i)->getPoints();

				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
				this->enemies->erase(i);
				break;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update(this->window->getSize());
	this->updateBullets();

	this->enemies->update(this->window, this->player);

	this->updateCombat();
	this->gui->update(this->points, this->player);
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
	//ToDo: figure out how to hide this inside player class
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f - this->textures["BULLET"]->getSize().x/2,
				this->player->getPos().y,
				0.f,
				-1.f,
				5.f
			));
	}
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
	this->window->draw(this->worldBackground);

	this->player->render(this->window);

	this->enemies->render(this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->gui->render(this->window);

	//game over screen
	if (!this->player->isAlive()) {
		this->gui->renderGameOver(this->window);
	}

	this->window->display();
}
