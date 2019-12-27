#pragma once
#include "AGameObject.h"
class AirplaneSupport :
	public AGameObject
{
	public:
		AirplaneSupport(string name);
		void initialize();
		//void processInput(sf::Event event);
		//void update(sf::Time deltaTime);
};

