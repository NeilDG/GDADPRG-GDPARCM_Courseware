#pragma once
#include "AView.h"
#include "UIButtonInputController.h"
class QuitScreen :	public AView, public ButtonListener
{
	public:
		QuitScreen(string name);
		~QuitScreen();

		void initialize();
		void onButtonClick(UIButton* button);
		void onButtonReleased(UIButton* button);
};

