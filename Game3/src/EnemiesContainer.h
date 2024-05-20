#pragma once

#include <iostream>

#include "TemplatedContainer.h"
#include "Enemy.h"
#include "Player.h"

/*
* Class containing logic of Enemies collection
*/
class EnemiesContainer : public TemplatedContainer<Enemy*>
{
private:
	float spawnTimer;
	float spawnTimerMax;

	void spawn(sf::RenderWindow* window);
	void updateEnemies();
	void updateBottomCollision(sf::RenderWindow* window);
	void updatePlayerCollision(Player* player);
public:
	EnemiesContainer();
	~EnemiesContainer();

	void erase(int pos) override;

	void update(sf::RenderWindow* window, Player* player);
	void render(sf::RenderTarget* target) const;
};

