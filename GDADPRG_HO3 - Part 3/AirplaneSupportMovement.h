#pragma once
#include "AComponent.h"
class AirplaneSupportMovement :	public AComponent
{

	public:
		AirplaneSupportMovement(string name);
		~AirplaneSupportMovement();
		void perform();


	private:
		const float SPEED_MULTIPLIER = 50.0f;
		float ticks = 0.0f;
		bool moveLeft = false;
		bool moveRight = true;
};

