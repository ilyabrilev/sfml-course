#include "EnemiesContainer.h"

EnemiesContainer::EnemiesContainer()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = spawnTimerMax;
}

EnemiesContainer::~EnemiesContainer()
{
	for (int i = 0; i < this->size(); i++)
	{
		delete this->at(i);
	}
}

void EnemiesContainer::spawn(sf::RenderWindow* window)
{
	//spawn
	this->spawnTimer += 1.f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->push_back(new Enemy(window->getSize().x));
		this->spawnTimer = 0.f;
	}
}

void EnemiesContainer::updateEnemies()
{
	//update each enemy
	for (int i = 0; i < this->size(); i++)
	{
		this->at(i)->update();
	}
}

void EnemiesContainer::updateBottomCollision(sf::RenderWindow* window)
{	
	//remove at the bottom
	unsigned windowY = window->getSize().y;
	for (int i = 0; i < this->size(); i++)
	{
		//enemy removed from the bottom
		if (this->at(i)->getBounds().top > windowY)
		{
			//delete an enemy
			this->erase(i);
		}
	}
}

void EnemiesContainer::erase(int pos) {
	delete this->at(pos);
	TemplatedContainer::erase(pos);
}

void EnemiesContainer::updatePlayerCollision(Player* player)
{
	sf::FloatRect playerBounds = player->getBounds();
	//Update (remove at the bottom)
	for (int i = 0; i < this->size(); i++)
	{
		if (this->at(i)->getBounds().intersects(playerBounds))
		{
			//delete enemy if it toches a player
			player->loseHp(this->at(i)->getDamage());
			this->erase(i);
		}
	}
}

void EnemiesContainer::update(sf::RenderWindow* window, Player* player)
{
	this->spawn(window);
	this->updateEnemies();
	this->updateBottomCollision(window);
	this->updatePlayerCollision(player);
}

void EnemiesContainer::render(sf::RenderTarget* target) const
{
	for (int i = 0; i < this->size(); i++)
	{
		this->at(i)->render(target);
	}
}
