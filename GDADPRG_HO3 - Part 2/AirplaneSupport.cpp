#include "AirplaneSupport.h"
#include "TextureManager.h"

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
	//do not do anything since airplane support is parented to airplane player.
	//it will follow its transform
}
