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

sf::Sprite* AGameObject::getSprite()
{
	return this->sprite;
}

void AGameObject::attachChild(AGameObject* child) {
	this->childList.push_back(child);
	child->initialize(); //initialize when attaching to child

	//set reference to child
	child->parent = this;
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

void AGameObject::setScale(float x, float y)
{
	if (this->sprite != NULL) {
		this->sprite->setScale(x, y);
	}
}

sf::FloatRect AGameObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

//SFML global bounds function does not take into account parent-child hierarchies!
//this is the fix
sf::FloatRect AGameObject::getWorldBounds() {
	sf::FloatRect bounds = this->sprite->getGlobalBounds();

	AGameObject* parentObj = this->parent;
	sf::Transform transform = sf::Transform::Identity;
	while (parentObj != NULL) {
		transform *= parentObj->getSprite()->getTransform();
		parentObj = parentObj->parent;
	}

	bounds = transform.transformRect(bounds);
	return bounds;
}

sf::Vector2f AGameObject::getPosition()
{
	return this->sprite->getPosition();
}

sf::Vector2f AGameObject::getScale()
{
	return this->sprite->getScale();
}

AGameObject::ObjectList AGameObject::getChildren() {
	return this->childList;
}

AGameObject* AGameObject::getParent()
{
	return this->parent;
}

/*void AGameObject::updateChildren(ObjectList objectList, sf::Time deltaTime) {
	for (int i = 0; i < objectList.size(); i++) {
		//replace with component update
		AGameObject::ComponentList componentList = objectList[i]->getComponentsOfType(AComponent::ComponentType::Script);
		for (int j = 0; j < componentList.size(); j++) {
			componentList[j]->setDeltaTime(deltaTime);
			componentList[j]->perform();
		}
		this->updateChildren(objectList[i]->getChildren(), deltaTime);
	}
}*/

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

//returns the first component by name
AComponent* AGameObject::findComponentByName(string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

//returns the first component by name and type
AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}

//returns all components of a given type
AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}
//recursive implementation. also searches in its children
AGameObject::ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < this->childList.size(); i++) {
		foundList = this->getComponentsRecursiveProper(this->childList[i], type, foundList);
	}

	return foundList;
}

AGameObject::ComponentList AGameObject::getComponentsRecursiveProper(AGameObject* object, AComponent::ComponentType type, ComponentList foundList)
{
	ObjectList children = object->childList;

	for (int i = 0; i < object->componentList.size(); i++) {
		if (object->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < children.size(); i++) {
		this->getComponentsRecursiveProper(children[i], type, foundList);
	}

	return foundList;
}

void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) {
	//apply drawing with parent-child relationship
	targetWindow->draw(*this->sprite, renderStates); //draw the object first
	renderStates.transform = this->sprite->getTransform() * renderStates.transform; //apply the transform to its children

	//draw its children
	for (int i = 0; i < this->childList.size(); i++) {
		AGameObject* child = this->childList[i];
		child->draw(targetWindow, renderStates);
	}
}
