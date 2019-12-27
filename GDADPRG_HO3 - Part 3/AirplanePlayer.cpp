#include "AirplanePlayer.h"
#include <iostream>
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "BaseRunner.h"

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
}

void AirplanePlayer::processInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
		this->moveUp = true;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
		this->moveDown = true;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
		this->moveRight = true;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
		this->moveLeft = true;
	}
	else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
		this->moveUp = false;
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
		this->moveDown = false;
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
		this->moveRight = false;
	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) {
		this->moveLeft = false;
	}
	
}

void AirplanePlayer::update(sf::Time deltaTime){

	sf::Vector2f offset(0.0f, 0.0f);
	if (this->moveUp) {
		offset.y -= this->SPEED_MULTIPLIER;
		this->sprite->move(offset * deltaTime.asSeconds());

	}
	else if (this->moveDown) {
		offset.y += this->SPEED_MULTIPLIER;
		this->sprite->move(offset * deltaTime.asSeconds());
	}
	else if (this->moveRight) {
		offset.x += this->SPEED_MULTIPLIER;
		this->sprite->move(offset * deltaTime.asSeconds());

	}
	else if (this->moveLeft) {
		offset.x -= this->SPEED_MULTIPLIER;
		this->sprite->move(offset * deltaTime.asSeconds());

	}
}




