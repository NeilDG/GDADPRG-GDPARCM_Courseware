#pragma once
#include "AGameObject.h"
//wrapper for SFML text
class UIText : public AGameObject
{
	public:
		UIText(string name);
		~UIText();

		void initialize();
		void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);

		void setText(string text);
		void setStyle(sf::Color fillColor, sf::Color outlineColor, float outlineThickness);
		void setSize(int size);
		void setPosition(float x, float y);
		void setScale(float x, float y);
		sf::Vector2f getPosition();
		sf::Vector2f getScale();
		string getText();

	protected:
		sf::Text* text = NULL;
};

