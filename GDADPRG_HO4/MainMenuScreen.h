#pragma once
#include "AView.h"
#include "UIButtonInputController.h"

class MainMenuScreen :	public AView, public ButtonListener
{
	public:
		MainMenuScreen(string name);
		~MainMenuScreen();

		void initialize();
		void onButtonClick(UIButton* button);
		void onButtonReleased(UIButton* button);
};

