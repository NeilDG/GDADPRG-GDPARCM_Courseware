#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

class AGameObject: sf::NonCopyable
{
	public:
		AGameObject(string name);
		~AGameObject();
		virtual void initialize() = 0;
		virtual void processInput(sf::Event event) = 0;
		virtual void update(sf::Time deltaTime) = 0;
		void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
		string getName();
		
		void attachChild(AGameObject* child);
		void detachChild(AGameObject* child);
		void setPosition(float x, float y);
			
		typedef vector<AGameObject*> List;

	protected:
		string name;
		sf::Sprite* sprite;
		sf::Texture* texture;
		List childList; //allow parenting of game objects


};

