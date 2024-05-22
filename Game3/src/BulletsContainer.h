#pragma once

#include "TemplatedContainer.h"
#include "Bullet.h"

class BulletsContainer : public TemplatedContainer<Bullet*>
{
private:
public:
	BulletsContainer();
	~BulletsContainer();

	void erase(int pos) override;

	void update();
	void render(sf::RenderTarget* target) const;

};

