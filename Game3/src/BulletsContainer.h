#pragma once

#include "TemplatedContainer.h"
#include "Bullet.h"

class BulletsContainer : public TemplatedContainer<Bullet*>
{
private:
public:
	BulletsContainer();
	~BulletsContainer();

	void update();
	void render(sf::RenderTarget* target) const;
};

