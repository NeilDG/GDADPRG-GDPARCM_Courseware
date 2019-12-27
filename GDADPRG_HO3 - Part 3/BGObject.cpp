#include "BGObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "BGMovement.h"

BGObject::BGObject(string name) : AGameObject(name)
{
}

void BGObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::BG, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setTextureRect(sf::IntRect(0,0,BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT * 8)); //make BG height x 3 to emulate repeating BG.
	this->sprite->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);

	BGMovement* movement = new BGMovement("BGMovement");
	this->attachComponent(movement);

}
