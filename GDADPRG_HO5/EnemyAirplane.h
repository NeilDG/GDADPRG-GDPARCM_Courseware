#pragma once
#include "AGameObject.h"
class EnemyAirplane :	public AGameObject
{
	public:
		EnemyAirplane(int counter, string name);
		~EnemyAirplane();
		void initialize();

	private:
		int counter = 0;
};

