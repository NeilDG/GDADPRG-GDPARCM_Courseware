#pragma once
#include "AView.h"
#include "UIButtonInputController.h"

class HUDScreen :	public AView, public ButtonListener
{
	public:
		HUDScreen(string name);
		~HUDScreen();

		void initialize();
		void onButtonClick(UIButton* button);
		void onButtonReleased(UIButton* button);
};

