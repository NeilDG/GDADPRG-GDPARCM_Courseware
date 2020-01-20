#pragma once
#include "APoolable.h"
#include "PhysicsManager.h"
class EnemyAirplane :	public APoolable, public Collision
{
	public:
		EnemyAirplane(string name);
		~EnemyAirplane();
		void initialize();
		void onRelease();
		void onActivate();
		APoolable* clone();

		void onCollisionEnter(AGameObject* contact);
		void onCollisionExit(AGameObject* contact);

	private:
		int counter = 0;
};

