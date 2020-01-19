#include "VectorUtils.h"

float VectorUtils::getDistance(sf::Vector2f v1, sf::Vector2f v2) {
	return sqrtf(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2));
}