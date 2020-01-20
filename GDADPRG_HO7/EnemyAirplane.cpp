#include "EnemyAirplane.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "ObjectPoolHolder.h"

EnemyAirplane::EnemyAirplane(string name): APoolable(name), Collision(this)
{
	
}

EnemyAirplane::~EnemyAirplane()
{
	AGameObject::~AGameObject();
}

void EnemyAirplane::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Avenger, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, -30);
	//randomize
	this->sprite->move(rand() % 300 - rand() % 300, 0);
	this->sprite->setRotation(180); //must face towards player

	EnemyBehavior* behavior = new EnemyBehavior("EnemyBehavior");
	this->attachComponent(behavior);

}

void EnemyAirplane::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this);
}

void EnemyAirplane::onActivate()
{
	//reset state
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyBehavior");
	behavior->reset();
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, -30);
	//randomize
	this->sprite->move(rand() % 300 - rand() % 300, 0);

	PhysicsManager::getInstance()->trackObject(this);
}

APoolable* EnemyAirplane::clone()
{
	APoolable* copyObj = new EnemyAirplane(this->name);
	return copyObj;
}

void EnemyAirplane::onCollisionEnter(AGameObject* contact)
{
	if (contact->getName().find("projectile") != std::string::npos) {
		//std:cout << "Collided with " << contact->getName() << "\n";
		GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
		enemyPool->releasePoolable((APoolable*)this);
	}
}

void EnemyAirplane::onCollisionExit(AGameObject* contact)
{
	
}
