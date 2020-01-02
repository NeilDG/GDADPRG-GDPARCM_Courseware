#include "QuitScreen.h"
#include "UIText.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButton.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include <iostream>

QuitScreen::QuitScreen(string name): AView(name), ButtonListener()
{
}

QuitScreen::~QuitScreen()
{
	delete this->displayText;
	AView::~AView();
	ButtonListener::~ButtonListener();
}

void QuitScreen::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::UI_BG, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);

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
	button_1Text->setText("YES");

	button = new UIButton(normalTexture, pressedTexture, "button_2");
	this->attachChild(button);
	button->setPosition(textureSize.x / 2 + 150, textureSize.y / 2 + 150);
	button->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_2Text = new UIText("text_2");
	button->attachChild(button_2Text);
	button_2Text->setPosition(button->getLocalBounds().width - 35, button->getLocalBounds().height + 50);
	button_2Text->setSize(100);
	button_2Text->setText("NO");

	this->displayText = new UIText("displayText");
	this->attachChild(this->displayText);
	this->displayText->setPosition(textureSize.x / 2, textureSize.y / 2 - 100);
	this->displayText->setSize(40);

	if (this->forMainMenu) {
		this->displayText->setText("Are you sure you want \n to quit the game?");
	}
	else {
		this->displayText->setText("Are you sure you want \n to return to the main menu?");
	}
	

	ApplicationManager::getInstance()->pauseApplication();
}

void QuitScreen::onButtonClick(UIButton* button)
{

}

void QuitScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "button_1") {
		if (this->forMainMenu) {
			ApplicationManager::getInstance()->applicationQuit();
		}
		else {
			std::cout << "Return to main menu! \n";
			SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
			ApplicationManager::getInstance()->resumeApplication();
		}
	}
	else if (button->getName() == "button_2") {
		ApplicationManager::getInstance()->resumeApplication();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}

void QuitScreen::markMainMenuQuit()
{
	this->forMainMenu = true;
}

void QuitScreen::markGameQuit()
{
	this->forMainMenu = false;
}
