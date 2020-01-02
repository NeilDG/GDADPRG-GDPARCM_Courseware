#pragma once
#include "AView.h"
#include "UIButtonInputController.h"
class SamplePopupScreen :	public AView, public ButtonListener
{
	public:
		SamplePopupScreen(string name);
		~SamplePopupScreen();

		void initialize();
		void onButtonClick(UIButton* button);
		void onButtonReleased(UIButton* button);
};

