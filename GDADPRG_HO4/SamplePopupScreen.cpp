#include "SamplePopupScreen.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"

SamplePopupScreen::SamplePopupScreen(string name):AView(name)
{

}

SamplePopupScreen::~SamplePopupScreen()
{
	AView::~AView();
}

void SamplePopupScreen::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::BG, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setColor(sf::Color::Cyan);
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);
	this->setScale(0.75f, 0.75f);

	sf::Texture* normalTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonNormal, 0);
	sf::Texture* pressedTexture = TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::ButtonPressed, 0);

	UIButton* button = new UIButton(normalTexture, pressedTexture, "button_1");
	this->attachChild(button);
	button->setPosition(textureSize.x / 2, textureSize.y / 2 + 100);
	button->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(button->getLocalBounds().width, button->getLocalBounds().height - 30);
	button_1Text->setSize(100);
	button_1Text->setText("CLOSE");

	UIText* displayText = new UIText("displayText");
	this->attachChild(displayText);
	displayText->setPosition(textureSize.x / 2, textureSize.y / 2 - 100);
	displayText->setSize(40);
	displayText->setText("This is another popup");
}

void SamplePopupScreen::onButtonClick(UIButton* button)
{
	
}

void SamplePopupScreen::onButtonReleased(UIButton* button)
{
	GameObjectManager::getInstance()->deleteObject(this);
}
