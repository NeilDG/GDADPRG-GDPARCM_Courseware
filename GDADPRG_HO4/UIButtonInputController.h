#pragma once
#include "GenericInputController.h"

class UIButton; //forward declaration to avoid circular dependency
class ButtonListener
{
public:
	ButtonListener();
	~ButtonListener();

	virtual void onButtonClick(UIButton* button) = 0;
	virtual void onButtonReleased(UIButton* button) = 0;

};

class UIButtonInputController :	public GenericInputController
{
	public:
		UIButtonInputController(string name, ButtonListener* buttonListener);
		~UIButtonInputController();

		ButtonListener* buttonListener;

		void perform();
};



