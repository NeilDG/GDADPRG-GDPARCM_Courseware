#include "SpikePowerup.h"
#include "TextureManager.h"
#include "RotateMovement.h"
#include "AirplaneSupportMovement.h"

SpikePowerup::SpikePowerup(string name): AGameObject(name)
{
}

SpikePowerup::~SpikePowerup()
{
	AGameObject::~AGameObject();
}

void SpikePowerup::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Spike, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(0, 0);
	this->sprite->setScale(0.15f, 0.15f);

	//assign rotation movement
	RotateMovement* rotateMovement = new RotateMovement("RotateMovement");
	this->attachComponent(rotateMovement);

	//assign side move
	//AirplaneSupportMovement* sideMovement = new AirplaneSupportMovement("AirplaneSupportMovement");
	//this->attachComponent(sideMovement);
}
