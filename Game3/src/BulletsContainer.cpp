#include "BulletsContainer.h"

BulletsContainer::BulletsContainer()
{
}

BulletsContainer::~BulletsContainer()
{
	for (int i = 0; i < this->size(); i++)
	{
		delete this->at(i);
	}
}

void BulletsContainer::erase(int pos) {
	delete this->at(pos);
	TemplatedContainer::erase(pos);
}

void BulletsContainer::update()
{
	for (int i = 0; i < this->size(); i++)
	{
		Bullet* bullet = this->at(i);
		bullet->update();
		//bullet culling top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//delete a bullet
			this->erase(i);
		}
	}
}

void BulletsContainer::render(sf::RenderTarget* target) const
{
	for (int i = 0; i < this->size(); i++)
	{
		this->at(i)->render(target);
	}
}
