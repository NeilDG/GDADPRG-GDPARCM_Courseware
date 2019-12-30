#include "EnemyBehavior.h"
#include "AGameObject.h"
#include <iostream>
EnemyBehavior::EnemyBehavior(string name): AComponent(name, Script)
{
	//this->delay = (rand() % 3);
	this->movementType = Delay;
}

EnemyBehavior::~EnemyBehavior()
{
	AComponent::~AComponent();
}

void EnemyBehavior::perform()
{
	this->ticks += this->deltaTime.asSeconds();
	sf::Sprite* sprite = this->getOwner()->getSprite();

	if (this->ticks > this->delay && this->movementType == Delay) {
		this->ticks = 0.0f;
		this->movementType = Forward;
		std::cout << "Ticks greater! " << this->getOwner()->getName() << "\n";
	}
	else {
		//std::cout << "Ticks value: "<< this->ticks << "from " << this->getOwner()->getName() << "\n";
	}

	if (this->ticks > 2.0f && this->movementType != Side) {
		//change movement type every X seconds
		int counter = (this->movementType + 1) % EnemyMovementType::Side + 1;
		this->movementType = (EnemyMovementType) counter;
		this->ticks = 0.0f;
	}

	if (this->movementType == Forward) {
		sprite->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
	}
	else if (this->movementType == SlowForward) {
		sprite->move(0, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER / 2.0f));
	}
	else if (this->movementType == Side) {
		sprite->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
	}
}

void EnemyBehavior::addDelay(float delay)
{
	this->delay += delay;
	std::cout << "Delay: " << this->delay << "\n";
}
