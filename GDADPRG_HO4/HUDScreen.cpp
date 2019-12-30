#include "HUDScreen.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButton.h"
#include "UIText.h"
#include "QuitScreen.h"
#include "GameObjectManager.h"

HUDScreen::HUDScreen(string name): AView(name), ButtonListener()
{

}

HUDScreen::~HUDScreen()
{
	AView::~AView();
}

void HUDScreen::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::HUD_BG, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(BaseRunner::WINDOW_WIDTH - 240, BaseRunner::WINDOW_HEIGHT - 50);

	sf::Texture* normalTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonNormal, 0);
	sf::Texture* pressedTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonPressed, 0);
	UIButton* quitBtn = new UIButton(normalTexture, pressedTexture, "quitBtn");
	this->attachChild(quitBtn);
	quitBtn->setPosition(textureSize.x - 60, textureSize.y - 35);
	quitBtn->setScale(0.15f, 0.15f);
	quitBtn->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	//do not make as a button child. difficult to position
	this->attachChild(button_1Text);
	button_1Text->setPosition(textureSize.x - 60, textureSize.y - 35);
	button_1Text->setStyle(sf::Color::White, sf::Color::Black, 2);
	button_1Text->setSize(18);
	button_1Text->setText("QUIT");

}

void HUDScreen::onButtonClick(UIButton* button)
{
}

void HUDScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "quitBtn") {
		QuitScreen* quitScreen = new QuitScreen("quitScreen");
		GameObjectManager::getInstance()->addObject(quitScreen);
	}
}
