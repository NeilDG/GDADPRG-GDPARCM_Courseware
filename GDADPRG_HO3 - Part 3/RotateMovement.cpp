#include "RotateMovement.h"
#include "AGameObject.h"
#include "BaseRunner.h"

RotateMovement::RotateMovement(string name):AComponent(name, Script)
{
}

RotateMovement::~RotateMovement()
{
	AComponent::~AComponent();
}

void RotateMovement::perform()
{
	sf::Sprite* sprite = this->getOwner()->getSprite();
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > BaseRunner::TIME_PER_FRAME.asSeconds()) {
		this->ticks = 0.0f;
		sprite->rotate(4);
	}
}

