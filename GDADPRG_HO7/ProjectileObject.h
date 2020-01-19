#pragma once
#include "AGameObject.h"
#include "APoolable.h"
#include "ProjectileMovement.h"
class ProjectileObject :	public APoolable
{
	public:
		ProjectileObject(string name);
		~ProjectileObject();
		void initialize();
		void onRelease();
		void onActivate();
		APoolable* clone();

	private:
		ProjectileMovement* projectileMovement;

};

