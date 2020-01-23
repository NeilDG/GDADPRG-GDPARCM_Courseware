#include "ProjectileObject.h"
#include "TextureManager.h"
#include "ProjectileMovement.h"
#include "ProjectileHandler.h"
#include "AirplanePlayer.h"
#include "GameObjectManager.h"
#include <string>
#include "ObjectPoolHolder.h"
#include "UIManager.h"
#include "HUDScreen.h"

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
	this->hasHit = false;

	PhysicsManager::getInstance()->trackObject(this);
}

APoolable* ProjectileObject::clone()
{
	APoolable* copyObj = new ProjectileObject(this->name);
	return copyObj;
}

void ProjectileObject::onCollisionEnter(AGameObject* contact)
{
	if (contact->getName().find("enemy") != std::string::npos && !this->hasHit) {
		//std:cout << "Collided with " << contact->getName() << "\n";
		this->hasHit = true;
		GameObjectPool* projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
		projectilePool->releasePoolable((APoolable*)this);

		UIData* scoreData = UIManager::getInstance()->getUIData(HUDScreen::SCORE_TEXT_KEY);
		scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) + 100);
		scoreData->refreshTextFromData(HUDScreen::SCORE_TEXT_KEY, UIManager::SCORE_UI_KEY, "SCORE: ");
	}
}

void ProjectileObject::onCollisionExit(AGameObject* contact)
{

}
