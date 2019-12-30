#include "AirplaneSupportMovement.h"
#include "AGameObject.h"
#include <iostream>

AirplaneSupportMovement::AirplaneSupportMovement(string name): AComponent(name, Script)
{
}

AirplaneSupportMovement::~AirplaneSupportMovement()
{
	AComponent::~AComponent();
}

void AirplaneSupportMovement::perform()
{
	sf::Sprite* sprite = this->getOwner()->getSprite();
	sf::Vector2f offset(0.0f, 0.0f);

	this->ticks += this->deltaTime.asSeconds();
	if (this->moveRight) {
		offset.x += this->SPEED_MULTIPLIER;
		sprite->move(offset * deltaTime.asSeconds());
	}
	else if (this->moveLeft) {
		offset.x -= this->SPEED_MULTIPLIER;
		sprite->move(offset * deltaTime.asSeconds());
	}

	if (this->ticks > 2.0f && this->moveRight) {
		this->moveRight = false;
		this->moveLeft = true;
		this->ticks = 0.0f;
	}
	else if (this->ticks > 2.0f && this->moveLeft) {
		this->moveLeft = false;
		this->moveRight = true;
		this->ticks = 0.0f;
	}
}
