#include "BaseRunner.h"
#include "TextureManager.h"
#include <iostream>

const sf::Time HO2::BaseRunner::TimePerFrame = sf::seconds(1.f / 60.f);

HO2::BaseRunner::BaseRunner(): 
	window(sf::VideoMode(1024, 768), "HO: Asset Management", sf::Style::Close)
{

	TextureManager::getInstance()->loadAll();
	Entity* entity = new Entity();
	entity->updateTexture((TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Bed, 0)));
	entity->getSprite()->setPosition(0.0f, 0.0f);
	this->entityList.push_back(*entity);

	entity = new Entity();
	entity->updateTexture((TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Bench, 0)));
	entity->getSprite()->setPosition(400.0f, 400.0f);
	this->entityList.push_back(*entity);
}
void HO2::BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void HO2::BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {

		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void HO2::BaseRunner::update(sf::Time elapsedTime) {

}

void HO2::BaseRunner::render() {
	this->window.clear();

	for (int i = 0; i < this->entityList.size(); i++) {
		this->window.draw(*this->entityList[i].getSprite());
		cout << "Element " << i << "\n";
		cout << "Position " << this->entityList[i].getSprite()->getPosition().x;
	}
	
	this->window.display();
}