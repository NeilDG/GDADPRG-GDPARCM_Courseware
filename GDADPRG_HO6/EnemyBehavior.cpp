#include "EnemyBehavior.h"
#include "AGameObject.h"
#include <iostream>
#include "BaseRunner.h";
#include "ObjectPoolHolder.h"

EnemyBehavior::EnemyBehavior(string name): AComponent(name, Script)
{
	this->reset();
}

EnemyBehavior::~EnemyBehavior()
{
	AComponent::~AComponent();
}

void EnemyBehavior::perform()
{
	this->ticks += this->deltaTime.asSeconds();
	sf::Sprite* sprite = this->getOwner()->getSprite();

	/*if (this->ticks > this->delay && this->movementType == Delay) {
		this->ticks = 0.0f;
		this->movementType = Forward;
		std::cout << "Ticks greater! " << this->getOwner()->getName() << "\n";
	}*/

	if (this->ticks > this->forwardDuration && this->movementType != Side) {
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
		if (this->getOwner()->getPosition().x > BaseRunner::WINDOW_WIDTH / 2) {
			sprite->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
		}
		else {
			sprite->move(-this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
		}

		//check if position is out of bounds, we can delete/return to pool
		if (this->getOwner()->getPosition().x > BaseRunner::WINDOW_WIDTH + 20 ||
			this->getOwner()->getPosition().x < -20) {
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG)->releasePoolable((APoolable*) this->getOwner());
		}
	}
}

void EnemyBehavior::configure(float delay)
{
	this->delay += delay;
}

void EnemyBehavior::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	this->forwardDuration = (rand() % 3) + 1.0f;
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
}
