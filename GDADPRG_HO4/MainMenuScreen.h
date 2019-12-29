#pragma once
#include "AView.h"
#include "UIButtonInputController.h"
#include "UIText.h"

class MainMenuScreen :	public AView, public ButtonListener
{
	public:
		MainMenuScreen(string name);
		~MainMenuScreen();

		void initialize();
		void onButtonClick(UIButton* button);
		void onButtonReleased(UIButton* button);

	private:
		UIText* displayText;
};

