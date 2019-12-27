#include "AirplaneSupport.h"
#include "TextureManager.h"
#include "AirplaneSupportMovement.h"
#include "RotateMovement.h"
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

	//assign logic component
	AirplaneSupportMovement* logicComponent = new AirplaneSupportMovement("AirplaneSupportMovement_1");
	this->attachComponent(logicComponent);
}
