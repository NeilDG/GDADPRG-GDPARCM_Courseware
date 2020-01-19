#pragma once
#include "AGameObject.h"
//represents an empty game object. use this to attach components that need to utilize the update() function, but not need to render
//a sprite
class EmptyGameObject :	public AGameObject
{
	public:
		EmptyGameObject(string name);
		~EmptyGameObject();
		void initialize();
		void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
};

