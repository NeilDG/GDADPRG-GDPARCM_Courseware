#include "Entity.h"
#include <iostream>

Entity::Entity() {
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	this->counter = new int;
	*this->counter = 0;
}

void Entity::updateTexture(sf::Texture *texture, TextureManager::AssetType assetType) {
	this->assetType = assetType;
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
	this->sprite->setOrigin(this->texture->getSize().x / 2, this->texture->getSize().y / 2);
}

void Entity::incrementTexture() {
	int size = TextureManager::getInstance()->getTextureLength(this->assetType);
	//cout << "Counter : " << *this->counter << " Size: " << size << "\n";
	*this->counter = (*this->counter + 1) % size;

	sf::Texture *texture = TextureManager::getInstance()->getTextureAt(this->assetType, *this->counter);
	this->texture = texture;
	this->sprite->setTexture(*this->texture);

	//cout << "Counter : " << *this->counter << " Size: " << size << "\n";
}

sf::Sprite* Entity::getSprite()
{
	return this->sprite;
}

TextureManager::AssetType Entity::getAssetType() {
	return this->assetType;
}