#include "PlayerInputController.h"

PlayerInputController::PlayerInputController(string name): GenericInputController(name)
{

}

PlayerInputController::~PlayerInputController()
{
	GenericInputController::~GenericInputController();
}

void PlayerInputController::perform()
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
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
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

bool PlayerInputController::isUp()
{
	return this->moveUp;
}

bool PlayerInputController::isDown()
{
	return this->moveDown;
}

bool PlayerInputController::isLeft()
{
	return this->moveLeft;
}

bool PlayerInputController::isRight()
{
	return this->moveRight;
}
