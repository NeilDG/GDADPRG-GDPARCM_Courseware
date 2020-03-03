#pragma once
#include "AGameObject.h"
class ZoomingPlane :
	public AGameObject
{
	public:
		ZoomingPlane(string name);
		~ZoomingPlane();
		void initialize();

		void setDelay(float seconds);
};

