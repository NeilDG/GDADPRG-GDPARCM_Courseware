#pragma once
#include "AComponent.h"
class ProjectileMovement :	public AComponent
{
	public:
		ProjectileMovement(string name);
		~ProjectileMovement();
		void perform();
		void reset();

	private:
		const float SPEED_MULTIPLIER = 240.0f;
		float ticks = 0.0f;
		float animTicks = 0.0f;
		int texIndex = 0;
		int maxTexLength = 0;

		void animate();

};

