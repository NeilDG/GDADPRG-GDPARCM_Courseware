#pragma once
#include "AView.h"
#include "UIButtonInputController.h"

class HUDScreen :	public AView, public ButtonListener
{
	public:
		static const string SCORE_TEXT_KEY;

		HUDScreen(string name);
		~HUDScreen();

		void initialize();
		void onButtonClick(UIButton* button);
		void onButtonReleased(UIButton* button);
};

