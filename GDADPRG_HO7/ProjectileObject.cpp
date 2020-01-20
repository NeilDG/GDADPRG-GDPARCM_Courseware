#include "ProjectileObject.h"
#include "TextureManager.h"
#include "ProjectileMovement.h"
#include "ProjectileHandler.h"
#include "AirplanePlayer.h"
#include "GameObjectManager.h"
#include <string>
#include "ObjectPoolHolder.h"

ProjectileObject::ProjectileObject(string name): APoolable(name), Collision(this)
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
	PhysicsManager::getInstance()->untrackObject(this);
}

void ProjectileObject::onActivate()
{
	//reset state
	AirplanePlayer* player = (AirplanePlayer*) GameObjectManager::getInstance()->findObjectByName("AirPlane");
	sf::Vector2f position = player->getPosition();
	this->setPosition(position.x, position.y);

	this->projectileMovement->reset();

	PhysicsManager::getInstance()->trackObject(this);
}

APoolable* ProjectileObject::clone()
{
	APoolable* copyObj = new ProjectileObject(this->name);
	return copyObj;
}

void ProjectileObject::onCollisionEnter(AGameObject* contact)
{
	if (contact->getName().find("enemy") != std::string::npos) {
		//std:cout << "Collided with " << contact->getName() << "\n";
		GameObjectPool* projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
		projectilePool->releasePoolable((APoolable*)this);
	}
}

void ProjectileObject::onCollisionExit(AGameObject* contact)
{

}
