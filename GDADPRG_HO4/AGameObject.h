#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "AComponent.h"

using namespace std;

class AGameObject: sf::NonCopyable
{
	public:
		AGameObject(string name);
		~AGameObject();
		virtual void initialize() = 0;

		//virtual void processInput(sf::Event event) = 0;
		//virtual void update(sf::Time deltaTime) = 0;
		void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
		string getName();
		sf::Sprite* getSprite();

		
		void attachChild(AGameObject* child);
		void detachChild(AGameObject* child);
		void setPosition(float x, float y);
		void setScale(float x, float y);

		sf::FloatRect getLocalBounds();
		sf::FloatRect getWorldBounds();

		sf::Vector2f getPosition();
		sf::Vector2f getScale();
			
		typedef vector<AGameObject*> ObjectList;
		typedef vector<AComponent*> ComponentList;

		ObjectList getChildren();
		AGameObject* getParent();
		//void updateChildren(ObjectList objectList, sf::Time deltaTime);

		void attachComponent(AComponent* component);
		void detachComponent(AComponent* component);

		AComponent* findComponentByName(string name);
		AComponent* findComponentOfType(AComponent::ComponentType type, string name);
		ComponentList getComponentsOfType(AComponent::ComponentType type);
		ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);

	protected:
		string name;
		sf::Sprite* sprite;
		sf::Texture* texture;

		ObjectList childList; //allow parenting of game objects
		ComponentList componentList;

		AGameObject* parent = NULL;


	private:
		ComponentList getComponentsRecursiveProper(AGameObject* object, AComponent::ComponentType type, ComponentList foundList);
		bool enabled = false;

};

