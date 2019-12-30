#include "UIText.h"
#include <iostream>
#include "TextureManager.h"
UIText::UIText(string name): AGameObject(name)
{

}

UIText::~UIText()
{
	delete this->text;

	std::cout << "Deleting UI TEXT " << this->getName() << "! Size: " << this->childList.size() << "\n";
	for (int i = 0; i < this->childList.size(); i++) {
		delete this->childList[i];
	}

	for (int i = 0; i < this->componentList.size(); i++) {
		delete this->componentList[i];
	}

	this->childList.clear(); this->childList.shrink_to_fit();
	this->componentList.clear(); this->componentList.shrink_to_fit();
}

void UIText::initialize()
{
	//declare a text to be used
	//font must be a pointer or else it gets immediately de-allocated.
	sf::Font* font = TextureManager::getInstance()->getFont(TextureManager::FontType::DefaultFont);
	this->text = new sf::Text();
	this->text->setFont(*font);
	this->setSize(40);
	this->setStyle(sf::Color::White, sf::Color::Black, 4.0f);
	this->text->setString("<Using placeholder!>");
}


//override draw by drawing text instead
void UIText::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	//apply drawing with parent-child relationship
	targetWindow->draw(*this->text, renderStates); //draw the object first
	renderStates.transform = this->text->getTransform() * renderStates.transform; //apply the transform to its children

	//draw its children
	for (int i = 0; i < this->childList.size(); i++) {
		AGameObject* child = this->childList[i];
		child->draw(targetWindow, renderStates);
	}
}

void UIText::setText(string text)
{
	this->text->setString(text);
	this->text->setOrigin(this->text->getLocalBounds().left +
		this->text->getLocalBounds().width / 2,
		this->text->getLocalBounds().top +
		this->text->getLocalBounds().height / 2); //auto align to center.
}

void UIText::setStyle(sf::Color fillColor, sf::Color outlineColor, float outlineThickness)
{
	this->text->setFillColor(fillColor);
	this->text->setOutlineColor(outlineColor);
	this->text->setOutlineThickness(outlineThickness);
}

void UIText::setSize(int size)
{
	sf::FloatRect bounds = this->getWorldBounds();
	this->text->setOrigin(bounds.left +
		bounds.width / 2,
		bounds.top +
		bounds.height / 2); //auto align to center.

	this->text->setCharacterSize(size);
}
	

//must be called after being registered to the game object manager or one of the parent game objects
void UIText::setPosition(float x, float y)
{
	if (this->text != NULL) {
		sf::FloatRect bounds = this->getWorldBounds();
		this->text->setOrigin(bounds.left +
			bounds.width / 2,
			bounds.top +
			bounds.height / 2); //auto align to center.
		this->text->setPosition(x, y);
	}
}

void UIText::setScale(float x, float y)
{
	if (this->text != NULL) {
		this->text->setScale(x, y);
	}
}

sf::FloatRect UIText::getLocalBounds()
{
	return sf::FloatRect();
}

sf::FloatRect UIText::getWorldBounds()
{
	sf::FloatRect bounds = this->text->getGlobalBounds();

	AGameObject* parentObj = this->parent;
	sf::Transform transform = sf::Transform::Identity;
	while (parentObj != NULL) {
		transform *= parentObj->getSprite()->getTransform();
		parentObj = parentObj->getParent();
	}

	bounds = transform.transformRect(bounds);
	return bounds;
}

sf::Vector2f UIText::getPosition()
{
	return this->text->getPosition();
}

sf::Vector2f UIText::getScale()
{
	return this->text->getScale();
}

string UIText::getText()
{
	return this->text->getString();
}
