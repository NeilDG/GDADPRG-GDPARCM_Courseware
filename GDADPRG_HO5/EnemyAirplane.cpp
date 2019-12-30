#include "EnemyAirplane.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "EnemyBehavior.h"
#include <iostream>

EnemyAirplane::EnemyAirplane(int counter, string name): AGameObject(name)
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
	this->sprite->setRotation(180); //must face towards player

	EnemyBehavior* behavior = new EnemyBehavior("EnemyBehavior");
	behavior->addDelay(this->counter);
	this->attachComponent(behavior);

}
