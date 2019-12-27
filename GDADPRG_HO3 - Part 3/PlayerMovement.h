#pragma once
#include "AComponent.h"
class PlayerMovement : public AComponent
{
	public:
		PlayerMovement(string name);
		~PlayerMovement();

		void perform();

	private:
		const float SPEED_MULTIPLIER = 300.0f;
};

