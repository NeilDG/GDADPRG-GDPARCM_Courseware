#include "ProjectileMovement.h"
#include "AGameObject.h"
#include "ObjectPoolHolder.h"
#include "TextureManager.h"

ProjectileMovement::ProjectileMovement(string name): AComponent(name, Script)
{
	this->maxTexLength = TextureManager::getInstance()->getTextureLength(TextureManager::AssetType::PROJECTILE);
}

ProjectileMovement::~ProjectileMovement()
{
	AComponent::~AComponent();
}

void ProjectileMovement::perform()
{
	sf::Sprite* sprite = this->getOwner()->getSprite();
	sprite->move(0, -this->deltaTime.asSeconds() * SPEED_MULTIPLIER);

	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > 3.0f) {
		ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG)->releasePoolable((APoolable*)this->getOwner());
	}

	this->animate();
}

void ProjectileMovement::reset()
{
	//reset variables
	this->ticks = 0.0f;
	this->animTicks = 0.0f;
	this->texIndex = 0;
	sf::Texture* nextTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::PROJECTILE, this->texIndex);
	this->getOwner()->getSprite()->setTexture(*nextTexture);
}

void ProjectileMovement::animate()
{
	this->animTicks += this->deltaTime.asSeconds();

	if (this->animTicks > 0.16f) {
		this->animTicks = 0.0f;

		if (this->texIndex + 1 < this->maxTexLength) {
			this->texIndex++;
			sf::Texture* nextTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::PROJECTILE, this->texIndex);
			this->getOwner()->getSprite()->setTexture(*nextTexture);
		}
	}
}

