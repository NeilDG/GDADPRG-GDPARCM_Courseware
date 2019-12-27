#include "BGMovement.h"
#include "AGameObject.h"
#include "BaseRunner.h"

BGMovement::BGMovement(string name): AComponent(name, Script)
{

}

BGMovement::~BGMovement()
{
	AComponent::~AComponent();
}

void BGMovement::perform()
{
	sf::Sprite* sprite = this->getOwner()->getSprite();

	//make BG scroll slowly
	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += this->SPEED_MULTIPLIER;
	sprite->move(offset * deltaTime.asSeconds());

	sf::Vector2f localPos = sprite->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0) {
		//reset position
		sprite->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
	}
	else {

	}
}
