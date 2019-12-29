#include "GenericInputController.h"

GenericInputController::GenericInputController(string name): AComponent(name, Input)
{
	
}

GenericInputController::~GenericInputController()
{
	AComponent::~AComponent();
}

void GenericInputController::assignEvent(sf::Event event)
{
	this->event = event;
}

void GenericInputController::perform()
{
	
}
