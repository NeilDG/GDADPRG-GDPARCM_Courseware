#include "MainMenuScreen.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButton.h"
#include <iostream>
#include "UIText.h"
#include "SamplePopupScreen.h"
#include "GameObjectManager.h"

MainMenuScreen::MainMenuScreen(string name):AView(name), ButtonListener()
{
}

MainMenuScreen::~MainMenuScreen()
{
	AView::~AView();
	delete this->displayText;
}

void MainMenuScreen::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::BG, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);
	//this->setScale(0.5f, 0.5f);

	sf::Texture* normalTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonNormal, 0);
	sf::Texture* pressedTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonPressed, 0);

	UIButton* button = new UIButton(normalTexture, pressedTexture, "button_1");
	this->attachChild(button);
	button->setPosition(textureSize.x / 2 - 150, textureSize.y / 2 + 150);
	button->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(button->getLocalBounds().width - 50, button->getLocalBounds().height + 50);
	button_1Text->setSize(100);
	button_1Text->setText("OPEN");

	button = new UIButton(normalTexture, pressedTexture, "button_2");
	this->attachChild(button);
	button->setPosition(textureSize.x / 2 + 150, textureSize.y / 2 + 150);
	button->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_2Text = new UIText("text_2");
	button->attachChild(button_2Text);
	button_2Text->setPosition(button->getLocalBounds().width - 35, button->getLocalBounds().height + 50);
	button_2Text->setSize(100);
	button_2Text->setText("EXIT");

	this->displayText = new UIText("displayText");
	this->attachChild(this->displayText);
	this->displayText->setPosition(textureSize.x / 2, textureSize.y / 2 - 100);
	this->displayText->setSize(40);
	this->displayText->setText("Hello world!");
}

void MainMenuScreen::onButtonClick(UIButton* button)
{
	this->displayText->setText("BUTTON PRESSED! " + button->getName());
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{
	this->displayText->setText("BUTTON RELEASED! " + button->getName());
	if (button->getName() == "button_1") {
		SamplePopupScreen* popupScreen = new SamplePopupScreen("SamplePopupScreen");
		GameObjectManager::getInstance()->addObject(popupScreen);
	}
}
