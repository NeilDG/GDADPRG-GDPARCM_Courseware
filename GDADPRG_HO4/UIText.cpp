#include "UIText.h"
#include <iostream>
UIText::UIText(string name): AGameObject(name)
{

}

UIText::~UIText()
{
	delete this->text->getFont();
	delete this->text;
	AGameObject::~AGameObject();
}

void UIText::initialize()
{
	//declare a text to be used
	//font must be a pointer or else it gets immediately de-allocated.
	sf::Font* font = new sf::Font();
	if (font->loadFromFile("Media/Sansation.ttf")) {
		std::cout << "Font loaded successfully! \n";
	}
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
	this->text->setCharacterSize(size);
	this->text->setOrigin(this->text->getLocalBounds().left + 
		this->text->getLocalBounds().width / 2,
		this->text->getLocalBounds().top +
		this->text->getLocalBounds().height / 2); //auto align to center.
}

//must be called after being registered to the game object manager or one of the parent game objects
void UIText::setPosition(float x, float y)
{
	if (this->text != NULL) {
		this->text->setPosition(x, y);
	}
}

void UIText::setScale(float x, float y)
{
	if (this->text != NULL) {
		this->text->setScale(x, y);
	}
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
