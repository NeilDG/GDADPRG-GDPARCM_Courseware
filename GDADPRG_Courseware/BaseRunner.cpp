#include "BaseRunner.h"
#include "TextureManager.h"
#include <iostream>
#include "VectorUtils.h"

const sf::Time HO2::BaseRunner::TimePerFrame = sf::seconds(1.f / 60.f);

HO2::BaseRunner::BaseRunner(): 
	window(sf::VideoMode(1024, 768), "HO: Asset Management", sf::Style::Close)
{
	this->ticks = sf::Time::Zero;

	TextureManager::getInstance()->loadAll();
	Entity* entity = new Entity();
	entity->updateTexture(TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Bed, 0), TextureManager::AssetType::Bed);
	entity->getSprite()->setPosition(200.0f, 300.0f);
	this->entityList.push_back(*entity);

	entity = new Entity();
	entity->updateTexture(TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Bench, 0), TextureManager::AssetType::Bench);
	entity->getSprite()->setPosition(600.0f, 300.0f);
	this->entityList.push_back(*entity);

	entity = new Entity();
	entity->updateTexture(TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Box, 0), TextureManager::AssetType::Box);
	entity->getSprite()->setPosition(200.0f, 500.0f);
	this->entityList.push_back(*entity);

	entity = new Entity();
	entity->updateTexture(TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Coin, 0), TextureManager::AssetType::Coin);
	entity->getSprite()->setPosition(600.0f, 500.0f);
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

	sf::Mouse mouse;
	sf::Vector2f mousePos(mouse.getPosition(this->window).x, mouse.getPosition(this->window).y);

	this->changeableEntity = NULL;

	for (int i = 0; i < this->entityList.size(); i++) {
		Entity entity = this->entityList[i];
		float dist = VectorUtils::getDistance(mousePos, entity.getSprite()->getPosition());
		float bounds = entity.getSprite()->getGlobalBounds().width;
		if (dist < bounds) {
			this->changeableEntity = &this->entityList[i];
			break;
		}
	}
}

void HO2::BaseRunner::update(sf::Time elapsedTime) {
	this->ticks += elapsedTime;
	if (this->ticks.asSeconds() > 0.1167f && this->changeableEntity != NULL) { //computed by 7 frames divided by 60.0
		this->ticks = sf::Time::Zero;
		this->changeableEntity->incrementTexture();
	}
}

void HO2::BaseRunner::render() {
	this->window.clear();

	for (int i = 0; i < this->entityList.size(); i++) {
		this->window.draw(*this->entityList[i].getSprite());
	}
	
	this->window.display();
}