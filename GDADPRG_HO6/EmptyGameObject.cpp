#include "EmptyGameObject.h"

EmptyGameObject::EmptyGameObject(string name): AGameObject(name)
{

}

EmptyGameObject::~EmptyGameObject()
{
	AGameObject::~AGameObject();
}

void EmptyGameObject::initialize()
{
}

void EmptyGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	//do not draw anything, so use identity
	renderStates.transform = sf::Transform::Identity * renderStates.transform; //apply transform to its children

	//draw its children
	for (int i = 0; i < this->childList.size(); i++) {
		AGameObject* child = this->childList[i];
		child->draw(targetWindow, renderStates);
	}
}
