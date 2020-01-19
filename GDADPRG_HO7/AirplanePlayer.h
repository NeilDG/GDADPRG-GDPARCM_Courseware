#pragma once
#include "AGameObject.h"
#include <iostream>

using namespace std;

class AirplanePlayer : public AGameObject
{
	public: 
		AirplanePlayer(string name);
		~AirplanePlayer();
		void initialize();

};

