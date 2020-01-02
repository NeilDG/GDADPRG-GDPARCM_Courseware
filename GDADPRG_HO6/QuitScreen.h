#pragma once
#include "AView.h"
#include "UIButtonInputController.h"
#include "UIText.h"

class QuitScreen :	public AView, public ButtonListener
{
	public:
		QuitScreen(string name);
		~QuitScreen();

		void initialize();
		void onButtonClick(UIButton* button);
		void onButtonReleased(UIButton* button);

		void markMainMenuQuit();
		void markGameQuit();

	private:
		bool forMainMenu = false;
};

