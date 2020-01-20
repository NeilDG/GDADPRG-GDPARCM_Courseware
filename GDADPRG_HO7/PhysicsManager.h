#pragma once
#include "AComponent.h"
#include "AGameObject.h"
#include <unordered_map>
#include <vector>

class Collision;
typedef std::vector<Collision*> CollisionList;

class PhysicsManager :	public AComponent
{
	public:
		static void initialize(string name, AGameObject* parent);
		static void destroy();
		static PhysicsManager* getInstance();
		~PhysicsManager();

		void trackObject(Collision* object);
		void untrackObject(Collision* object);
		void perform();

	private:
		PhysicsManager(string name): AComponent(name, Script) {};
		PhysicsManager(PhysicsManager const&): AComponent(name, Script) {};             // copy constructor is private
		PhysicsManager& operator=(PhysicsManager const&) {};  // assignment operator is private
		static PhysicsManager* sharedInstance;

		CollisionList trackedObjects;
		CollisionList forCleaningObjects;

		void cleanUpObjects();
};

class Collision {

public:
	Collision(AGameObject* objRef);
	~Collision();

	virtual void onCollisionEnter(AGameObject* contact) = 0;
	virtual void onCollisionExit(AGameObject* contact) = 0;

	void setChecked(bool flag);
	bool isChecked();

	bool willCollide(Collision* another);
	bool alreadyCollided();
	void setAlreadyCollided(bool flag);

	AGameObject* getObjRef();
private:
	bool collided = false;
	bool checked = false;
	AGameObject* objRef = NULL;
	
};


