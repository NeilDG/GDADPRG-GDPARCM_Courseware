#include "AirplaneSupport.h"
#include "TextureManager.h"
#include <iostream>

AirplaneSupport::AirplaneSupport(string name):AGameObject(name)
{
}

void AirplaneSupport::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Raptor, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setPosition(0, 0);
}

void AirplaneSupport::processInput(sf::Event event)
{
}

void AirplaneSupport::update(sf::Time deltaTime)
{
	sf::Vector2f offset(0.0f, 0.0f);
	this->ticks += deltaTime.asSeconds();
	if (this->moveRight) {
		offset.x += this->SPEED_MULTIPLIER;
		this->sprite->move(offset * deltaTime.asSeconds());
	}
	else if (this->moveLeft) {
		offset.x -= this->SPEED_MULTIPLIER;
		this->sprite->move(offset * deltaTime.asSeconds());
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
