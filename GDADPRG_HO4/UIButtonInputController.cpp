#include "UIButtonInputController.h"
#include <iostream>
#include "UIButton.h"
#include "VectorUtils.h"
#include "BaseRunner.h"

UIButtonInputController::UIButtonInputController(string name, ButtonListener* buttonListener) : GenericInputController(name)
{
	this->buttonListener = buttonListener;
}

UIButtonInputController::~UIButtonInputController()
{
	AComponent::~AComponent();
}

void UIButtonInputController::perform()
{
	
	UIButton* button = (UIButton*)this->getOwner();
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		button->changeButtonToNormal();
		this->buttonListener->onButtonReleased(button);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		//check if button is within mouse coord
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::FloatRect bounds = button->getSprite()->getGlobalBounds();
		std::cout << "Mouse X: " << mousePos.x << " Y: " << mousePos.y << "\n";
		std::cout << "Bounds X: " << bounds.left << " Y: " << bounds.top << "\n";
		if (!bounds.contains(mousePos)) {
			return;
		}

		button->changeButtonToPressed();
		this->buttonListener->onButtonClick(button);
	}
	
}


ButtonListener::ButtonListener()
{
}

ButtonListener::~ButtonListener()
{
}
