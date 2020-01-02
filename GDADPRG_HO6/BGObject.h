#pragma once
#include "AGameObject.h"
class BGObject : public AGameObject
{
	public: 
		BGObject(string name);
		~BGObject();
		void initialize();
	private:
		const float SPEED_MULTIPLIER = 100.0f;
};

