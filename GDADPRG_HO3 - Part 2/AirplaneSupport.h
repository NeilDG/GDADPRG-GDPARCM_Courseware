#pragma once
#include "AGameObject.h"
class AirplaneSupport :
	public AGameObject
{
	public:
		AirplaneSupport(string name);
		void initialize();
		void processInput(sf::Event event);
		void update(sf::Time deltaTime);

	private:
		const float SPEED_MULTIPLIER = 50.0f;
		float ticks = 0.0f;
		bool moveLeft = false;
		bool moveRight = true;
};

