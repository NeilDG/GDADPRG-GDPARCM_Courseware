#pragma once
#include "AComponent.h"
class ProjectileHandler :	public AComponent
{
	public:
		ProjectileHandler(int numProjectiles, string name);
		~ProjectileHandler();
		void perform();

	private:
		const float SPAWN_INTERVAL = 0.15f;
		float ticks = 0.0f;
};

