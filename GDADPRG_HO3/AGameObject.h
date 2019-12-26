#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class AGameObject: sf::NonCopyable
{
	public:
		AGameObject(string name);
		~AGameObject();
		virtual void initialize() = 0;
		virtual void processInput(sf::Event event) = 0;
		virtual void update(sf::Time deltaTime) = 0;
		void draw(sf::RenderWindow* targetWindow);
		string getName();

	protected:
		string name;
		sf::Sprite* sprite;
		sf::Texture* texture;
};

