#pragma once
#include "AComponent.h"
class ZoomingComponent : public AComponent
{
	public:
		ZoomingComponent(string name);
		~ZoomingComponent();

		void perform();
		void setDelay(float seconds);

	private:
		float defaultSpeed = 75.0f;
		float increasedSpeed = 75.0f;
		float delay = 0.0f;
		float ticks = 0.0f;
};

