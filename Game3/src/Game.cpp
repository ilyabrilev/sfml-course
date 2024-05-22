#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->player = new Player(this->window->getSize());
	this->enemies = new EnemiesContainer();
	this->c_bullets = new BulletsContainer();
	this->gui = new Gui(this->window);
	this->initWorld();
	this->points = 0;

}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->gui;

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
	delete this->c_bullets;

	delete this->enemies;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game3", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	this->window->setPosition(sf::Vector2i(500, sf::VideoMode::getDesktopMode().height / 2 - 320));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTexture.loadFromFile(MAIN_DIRECTORY + "Textures/background1.jpg"))
	{
		std::cout << "ERROR::GAME:: Could not load background" << std::endl;
	}
	this->worldBackground.setTexture(this->worldBackgroundTexture);
}

// main game loop
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

void Game::update()
{
	this->updatePlayer();	
	this->c_bullets->update();

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

void Game::updatePlayer()
{
	this->player->update(this->window->getSize());
	this->player->updateAttack(*this->c_bullets);
}

void Game::updateBullets()
{
	this->c_bullets->update();

//	for (int i = 0; i < this->bullets.size(); i++)
//	{
//		Bullet* bullet = this->bullets[i];
//
//		bullet->update();
//
//		//bullet culling top of screen
//		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
//		{
//			//delete a bullet
//			delete bullet;
//			this->bullets.erase(this->bullets.begin() + i);
//		}
//	}
}

//update collision between bullets and enemies
void Game::updateCombat()
{
	for (int i = 0; i < this->enemies->size(); i++)
	{
		for (int j = 0; j < this->c_bullets->size(); j++)
		{
			if (this->c_bullets->at(j)->getBounds().intersects(this->enemies->at(i)->getBounds()))
			{
				this->points += this->enemies->at(i)->getPoints();
				this->c_bullets->erase(j);
				this->enemies->erase(i);
				break;
			}
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

	this->c_bullets->render(this->window);

	this->gui->render(this->window);

	//game over screen
	if (!this->player->isAlive()) {
		this->gui->renderGameOver(this->window);
	}

	this->window->display();
}
