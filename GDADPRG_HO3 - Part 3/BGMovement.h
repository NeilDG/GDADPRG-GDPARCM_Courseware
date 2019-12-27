#pragma once
#include "AComponent.h"
class BGMovement : public AComponent
{
	public:
		BGMovement(string name);
		~BGMovement();

		void perform();

	private:
		const float SPEED_MULTIPLIER = 100.0f;
};

