#include "EnemyAirplane.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "EnemyBehavior.h"
#include <iostream>

EnemyAirplane::EnemyAirplane(string name): APoolable(name)
{
	this->counter = counter;
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
	int random = rand() % 2;
	behavior->configure(this->counter);
	this->attachComponent(behavior);

}

void EnemyAirplane::onRelease()
{
	
}

void EnemyAirplane::onActivate()
{
	//reset state
}

APoolable* EnemyAirplane::clone()
{
	APoolable* copyObj = new EnemyAirplane(this->name);
	return copyObj;
}
