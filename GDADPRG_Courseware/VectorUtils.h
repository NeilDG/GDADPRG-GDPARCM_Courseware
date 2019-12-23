#pragma once
#include "SFML/Graphics.hpp";
class VectorUtils
{
	private:
		VectorUtils();

	public:
		static float getDistance(sf::Vector2f v1, sf::Vector2f v2);
};

