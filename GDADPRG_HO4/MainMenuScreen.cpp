#include "MainMenuScreen.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButton.h"
#include <iostream>
#include "GameObjectManager.h"
MainMenuScreen::MainMenuScreen(string name):AView(name), ButtonListener()
{
}

MainMenuScreen::~MainMenuScreen()
{
	AView::~AView();
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

	button = new UIButton(normalTexture, pressedTexture, "button_2");
	this->attachChild(button);
	button->setPosition(textureSize.x / 2 + 150, textureSize.y / 2 + 150);
	button->setScale(0.3f, 0.3f);
	button->setButtonListener(this);
}

void MainMenuScreen::onButtonClick(UIButton* button)
{
	std::cout << "BUTTON PRESSED! " +button->getName() + "\n";
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{
}
