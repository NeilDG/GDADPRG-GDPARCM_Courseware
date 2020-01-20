#include "PhysicsManager.h"
#include <iostream>

PhysicsManager* PhysicsManager::sharedInstance = NULL;

void PhysicsManager::initialize(string name, AGameObject* parent)
{
	sharedInstance = new PhysicsManager(name);
	parent->attachComponent(sharedInstance);
}

void PhysicsManager::destroy()
{
	delete sharedInstance;
}

PhysicsManager* PhysicsManager::getInstance()
{
	return sharedInstance;
}

PhysicsManager::~PhysicsManager()
{
	
}

void PhysicsManager::trackObject(Collision* object)
{
	this->trackedObjects.push_back(object);
}

void PhysicsManager::untrackObject(Collision* object)
{
	this->forCleaningObjects.push_back(object);
}

void PhysicsManager::perform()
{
	for (int i = 0; i < this->trackedObjects.size(); i++) {
		for (int j = 1; j < this->trackedObjects.size(); j++) {
			//check collision between two objects
			if (this->trackedObjects[i]->willCollide(this->trackedObjects[j])
				&& !this->trackedObjects[i]->alreadyCollided()
				&& !this->trackedObjects[j]->alreadyCollided()) {
				this->trackedObjects[i]->onCollisionEnter(this->trackedObjects[j]->getObjRef());
				this->trackedObjects[j]->onCollisionEnter(this->trackedObjects[i]->getObjRef());

				this->trackedObjects[i]->setAlreadyCollided(true);
				this->trackedObjects[j]->setAlreadyCollided(true);
			}

			else if(!this->trackedObjects[i]->willCollide(this->trackedObjects[j])
				&& this->trackedObjects[i]->alreadyCollided()
				&& this->trackedObjects[j]->alreadyCollided()) {
				this->trackedObjects[i]->onCollisionExit(this->trackedObjects[j]->getObjRef());
				this->trackedObjects[j]->onCollisionExit(this->trackedObjects[i]->getObjRef());

				this->trackedObjects[i]->setAlreadyCollided(false);
				this->trackedObjects[j]->setAlreadyCollided(false);
			}
			
		}
	}

	for (int i = 0; i < this->trackedObjects.size(); i++) {
		this->trackedObjects[i]->setChecked(false);
	}

	this->cleanUpObjects();
}

void PhysicsManager::cleanUpObjects()
{
	for (int i = 0; i < this->forCleaningObjects.size(); i++) {
		this->trackedObjects.erase(this->trackedObjects.begin() + i);
	}

	this->forCleaningObjects.clear();
	//std::cout << "Size of tracked objects: " << this->trackedObjects.size() << "\n";
	//std::cout << "Size of cleaning objects: " << this->forCleaningObjects.size() << "\n";
}

Collision::Collision(AGameObject* objRef)
{
	this->objRef = objRef;
}

Collision::~Collision()
{
}


void Collision::setChecked(bool flag)
{
	this->checked = flag;
}

bool Collision::isChecked()
{
	return this->checked;
}

bool Collision::willCollide(Collision* another)
{
	
	sf::FloatRect A = this->objRef->getWorldBounds();
	sf::FloatRect B = another->objRef->getWorldBounds();

	return A.intersects(B);
}

bool Collision::alreadyCollided()
{
	return this->collided;
}

void Collision::setAlreadyCollided(bool flag)
{
	this->collided = flag;
}

AGameObject* Collision::getObjRef()
{
	return this->objRef;
}
