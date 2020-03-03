#include "ZoomingComponent.h"
#include "AGameObject.h"

ZoomingComponent::ZoomingComponent(string name) : AComponent(name, Script)
{
	this->increasedSpeed = this->defaultSpeed * (2 + (rand() % 2));
}

ZoomingComponent::~ZoomingComponent()
{
	AComponent::~AComponent();
}

void ZoomingComponent::perform()
{
	sf::Sprite* sprite = this->getOwner()->getSprite();

	this->ticks += this->deltaTime.asSeconds();
	
	if (this->ticks < delay) {
		return;
	}

	if (this->ticks > 2.0f) {
		sf::Vector2f offset(0.0f, 0.0f);
		offset.y -= this->increasedSpeed;
		sprite->move(offset * this->deltaTime.asSeconds());
	}
	else {
		sf::Vector2f offset(0.0f, 0.0f);
		offset.y -= this->defaultSpeed;
		sprite->move(offset * this->deltaTime.asSeconds());
	}
}

void ZoomingComponent::setDelay(float seconds)
{
	this->delay = seconds;
}
