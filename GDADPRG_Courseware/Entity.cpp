#include "Entity.h"

Entity::Entity() {
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
}

void Entity::updateTexture(sf::Texture *texture) {
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}

sf::Sprite* Entity::getSprite()
{
	return this->sprite;
}