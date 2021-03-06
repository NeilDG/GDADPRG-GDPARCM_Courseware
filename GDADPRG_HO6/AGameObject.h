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
		virtual ~AGameObject();
		virtual void initialize() = 0;

		//virtual void processInput(sf::Event event) = 0;
		//virtual void update(sf::Time deltaTime) = 0;
		virtual void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
		string getName();
		sf::Sprite* getSprite();

		void attachChild(AGameObject* child);
		void detachChild(AGameObject* child);
		virtual void setPosition(float x, float y);
		virtual void setScale(float x, float y);

		virtual sf::FloatRect getLocalBounds();
		virtual sf::FloatRect getWorldBounds();

		virtual sf::Vector2f getPosition();
		virtual sf::Vector2f getScale();
			
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

		void setEnabled(bool flag);
		bool isEnabled();

	protected:
		string name;
		sf::Sprite* sprite;
		sf::Texture* texture;

		ObjectList childList; //allow parenting of game objects
		ComponentList componentList;

		AGameObject* parent = NULL;


	private:
		ComponentList getComponentsRecursiveProper(AGameObject* object, AComponent::ComponentType type, ComponentList foundList);
		bool enabled = true;

};

