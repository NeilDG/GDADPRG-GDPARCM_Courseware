#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
}

AGameObject::~AGameObject() {
	delete this->sprite;
	delete this->texture;
}

string AGameObject::getName() {
	return this->name;
}

void AGameObject::draw(sf::RenderWindow* targetWindow) {
	if (this->sprite != NULL) {
		targetWindow->draw(*this->sprite);
	}
}
