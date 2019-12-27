#pragma once
#include "AComponent.h"
class SpriteRenderer :	public AComponent
{
	public:
		SpriteRenderer(string name);
		~SpriteRenderer();
		void assignTargetWindow(sf::RenderWindow* window);
		void assignSprite(sf::Sprite* sprite);
		void setRenderStates(sf::RenderStates renderStates);

		void perform();
	private:
		sf::RenderWindow* targetWindow;
		sf::Sprite* sprite;
		sf::RenderStates renderStates;
};

