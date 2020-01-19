#pragma once
#include "AGameObject.h"
#include <iostream>

using namespace std;

class AirplanePlayer : public AGameObject
{
	public: 
		static string AIRPLANE_NAME;
		static string PLAYER_INPUT_COMPONENT;
		AirplanePlayer(string name);
		~AirplanePlayer();
		void initialize();

};

