#include "AirplanePlayer.h"
#include <iostream>
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "BaseRunner.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"

AirplanePlayer::AirplanePlayer(string name) : AGameObject(name) {

}

void AirplanePlayer::initialize() {
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Eagle, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);
}




