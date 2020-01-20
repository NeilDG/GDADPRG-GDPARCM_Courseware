#pragma once
#include "AGameObject.h"
#include "APoolable.h"
#include "ProjectileMovement.h"
#include "PhysicsManager.h"

class ProjectileObject :	public APoolable, public Collision
{
	public:
		ProjectileObject(string name);
		~ProjectileObject();
		void initialize();
		void onRelease();
		void onActivate();
		APoolable* clone();

		void onCollisionEnter(AGameObject* contact);
		void onCollisionExit(AGameObject* contact);

	private:
		ProjectileMovement* projectileMovement;

};

