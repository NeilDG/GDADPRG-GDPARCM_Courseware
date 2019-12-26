#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "AirplanePlayer.h"
#include "BGObject.h"
#include "TextureManager.h"

const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {

	//load textures
	TextureManager::getInstance()->loadAll();

	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	AirplanePlayer* airplane = new AirplanePlayer("AirPlane");
	GameObjectManager::getInstance()->addObject(airplane);
	
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			update(TIME_PER_FRAME);
		}

		render();
	}
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}