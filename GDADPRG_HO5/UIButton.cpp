#include "UIButton.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButtonInputController.h"
#include <iostream>


UIButton::UIButton(sf::Texture* normalTexture, sf::Texture* pressedTexture, string name): AGameObject(name)
{
	this->normalTexture = normalTexture;
	this->pressedTexture = pressedTexture;
}

UIButton::~UIButton()
{
	/*if (this->listener != NULL) {
		delete this->listener;
	}*/
	AGameObject::~AGameObject();
}

void UIButton::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonNormal, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
}

void UIButton::setButtonListener(ButtonListener* listener)
{
	//assign input controller
	this->listener = listener;
	UIButtonInputController* inputController = new UIButtonInputController("UI_InputController", this->listener);
	this->attachComponent(inputController);
}

void UIButton::changeButtonToNormal()
{
	this->sprite->setTexture(*this->normalTexture);
}

void UIButton::changeButtonToPressed()
{
	this->sprite->setTexture(*this->pressedTexture);
}


