#include <stddef.h>
#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(string name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

List GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::processInput(sf::Event event) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		AGameObject::ComponentList componentList = this->gameObjectList[i]->getComponentsOfType(AComponent::ComponentType::Input);
		for (int j = 0; j < componentList.size(); j++) {
			componentList[j]->perform();
		}
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		AGameObject::ComponentList componentList = this->gameObjectList[i]->getComponentsOfType(AComponent::ComponentType::Script);
		for (int j = 0; j < componentList.size(); j++) {
			componentList[j]->setDeltaTime(deltaTime);
			componentList[j]->perform();
		}
		this->gameObjectList[i]->updateChildren(this->gameObjectList[i]->getChildren(), deltaTime);
	}
}

//draws the object if it contains a sprite
void GameObjectManager::draw(sf::RenderWindow* window) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->draw(window, sf::RenderStates::Default);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	//also initialize the oject
	this->gameObjectMap[gameObject->getName()] = gameObject;
	this->gameObjectList.push_back(gameObject);
	this->gameObjectMap[gameObject->getName()]->initialize();
}

//also frees up allocation of the object.
void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}
	
	delete gameObject;
}

void GameObjectManager::deleteObjectByName(string name) {
	AGameObject* object = this->findObjectByName(name);
	
	if (object != NULL) {
		this->deleteObject(object);
	}
}
