#include "AGameObject.h"
#include <iostream>

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

void AGameObject::attachChild(AGameObject* child) {
	this->childList.push_back(child);
	child->initialize(); //initialize when attaching to child
}

void AGameObject::detachChild(AGameObject* child)
{
	int index = -1;
	for (int i = 0; i < this->childList.size(); i++) {
		if (this->childList[i] == child) {
			index = i;
		}
	}

	if (index != -1) {
		this->childList.erase(this->childList.begin() + index);
	}
}

//must be called after being registered to the game object manager or one of the parent game objects
void AGameObject::setPosition(float x, float y)
{
	if (this->sprite != NULL) {
		this->sprite->setPosition(x, y);
	}
}

AGameObject::ObjectList AGameObject::getChildren() {
	return this->childList;
}

void AGameObject::updateChildren(ObjectList objectList, sf::Time deltaTime) {
	for (int i = 0; i < objectList.size(); i++) {
		objectList[i]->update(deltaTime);
		this->updateChildren(objectList[i]->getChildren(), deltaTime);
	}
}

void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) {
	//apply drawing with parent-child relationship
	targetWindow->draw(*this->sprite, renderStates); //draw the object first
	renderStates.transform = this->sprite->getTransform() * renderStates.transform; //apply the transform to its children
	//std::cout << "Drawing " + this->getName() + "\n";

	//draw its children
	for (int i = 0; i < this->childList.size(); i++) {
		AGameObject* child = this->childList[i];
		child->draw(targetWindow, renderStates);
	}
}
