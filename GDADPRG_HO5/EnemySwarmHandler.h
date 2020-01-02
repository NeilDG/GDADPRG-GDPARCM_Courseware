#pragma once
#include "AComponent.h"
//class handling N enemy airplanes. communicates with object pool
class EnemySwarmHandler :	public AComponent
{
	public:
		EnemySwarmHandler(int numEnemies, string name);
		~EnemySwarmHandler();
		void perform();

	private:
		const float SPAWN_INTERVAL = 0.01f;
		float ticks = 0.0f;
};

