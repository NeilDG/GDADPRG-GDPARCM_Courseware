#include "MainMenuScreen.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButton.h"
#include <iostream>
#include "UIText.h"
#include "SamplePopupScreen.h"
#include "GameObjectManager.h"
#include "QuitScreen.h"
#include "SceneManager.h"

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
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::MAIN_MENU_BG, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);

	sf::Texture* normalTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonNormal, 0);
	sf::Texture* pressedTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonPressed, 0);

	UIButton* button = new UIButton(normalTexture, pressedTexture, "main_menu_button_1");
	this->attachChild(button);
	button->setPosition(textureSize.x / 2, textureSize.y / 2 - 50);
	button->setScale(0.4f, 0.4f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("main_menu_text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(button->getLocalBounds().width / 2, button->getLocalBounds().height / 2);
	button_1Text->setSize(70);
	button_1Text->setStyle(sf::Color::White, sf::Color::Black, 6.0f);
	button_1Text->setText("PLAY GAME");

	UIButton* button_2 = new UIButton(normalTexture, pressedTexture, "main_menu_button_2");
	this->attachChild(button_2);
	button_2->setPosition(textureSize.x / 2, textureSize.y / 2 + 100);
	button_2->setScale(0.4f, 0.4f);
	button_2->setButtonListener(this);

	UIText* button_2Text = new UIText("main_menu_text_2");
	button_2->attachChild(button_2Text);
	button_2Text->setPosition(button_2->getLocalBounds().width / 2, button_2->getLocalBounds().height / 2);
	button_2Text->setSize(70);
	button_2Text->setStyle(sf::Color::White, sf::Color::Black, 6.0f);
	button_2Text->setText("QUIT");
}

void MainMenuScreen::onButtonClick(UIButton* button)
{
	
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "main_menu_button_1") {
		SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE_NAME);
	}
	else if (button->getName() == "main_menu_button_2") {
		QuitScreen* quitScreen = new QuitScreen("QuitScreen");
		quitScreen->markMainMenuQuit();
		GameObjectManager::getInstance()->addObject(quitScreen);
	}
}
