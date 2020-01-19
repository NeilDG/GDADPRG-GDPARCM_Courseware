#include "ProjectileObject.h"
#include "TextureManager.h"
#include "ProjectileMovement.h"
#include "ProjectileHandler.h"
#include "AirplanePlayer.h"
#include "GameObjectManager.h"

ProjectileObject::ProjectileObject(string name): APoolable(name)
{
}

ProjectileObject::~ProjectileObject()
{
	AGameObject::~AGameObject();
}

void ProjectileObject::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::PROJECTILE, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(0, 0);
	this->sprite->setScale(0.5f, 0.5f);
	this->sprite->setRotation(-90.0f);
	this->sprite->setColor(sf::Color(102, 51, 0));

	this->projectileMovement = new ProjectileMovement("projectile_movement");
	this->attachComponent(this->projectileMovement);

}

void ProjectileObject::onRelease()
{
}

void ProjectileObject::onActivate()
{
	//reset state
	AirplanePlayer* player = (AirplanePlayer*) GameObjectManager::getInstance()->findObjectByName("AirPlane");
	sf::Vector2f position = player->getPosition();
	this->setPosition(position.x, position.y);

	this->projectileMovement->reset();
}

APoolable* ProjectileObject::clone()
{
	APoolable* copyObj = new ProjectileObject(this->name);
	return copyObj;
}
