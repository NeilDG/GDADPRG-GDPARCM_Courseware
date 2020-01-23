#include "HUDScreen.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButton.h"
#include "UIText.h"
#include "QuitScreen.h"
#include "GameObjectManager.h"
#include "UIManager.h"

const string HUDScreen::SCORE_TEXT_KEY = "score_1";

HUDScreen::HUDScreen(string name): AView(name), ButtonListener()
{

}

HUDScreen::~HUDScreen()
{
	UIManager::getInstance()->removeData(SCORE_TEXT_KEY);
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

	UIText* scoreText = new UIText(HUDScreen::SCORE_TEXT_KEY);
	this->attachChild(scoreText);
	scoreText->setPosition(textureSize.x - 200, textureSize.y - 35);
	scoreText->setSize(20);
	scoreText->setText("SCORE: 100000");

	UIData* scoreData = UIManager::getInstance()->storeData(scoreText->getName());
	scoreData->bindUIText(scoreText);
	scoreData->putInt(UIManager::SCORE_UI_KEY, 0); //default score
	scoreData->refreshTextFromData(scoreText->getName(), UIManager::SCORE_UI_KEY, "SCORE: ");
}

void HUDScreen::onButtonClick(UIButton* button)
{
}

void HUDScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "quitBtn") {
		QuitScreen* quitScreen = new QuitScreen("QuitScreen");
		GameObjectManager::getInstance()->addObject(quitScreen);
	}
}
