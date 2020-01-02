#pragma once
#include "AComponent.h"
class RotateMovement :	public AComponent
{
	public:
		RotateMovement(string name);
		~RotateMovement();
		void perform();

	private:
		const float SPEED_MULTIPLIER = 50.0f;
		float ticks = 0.0f;
		float angle = 0.0f;

};

