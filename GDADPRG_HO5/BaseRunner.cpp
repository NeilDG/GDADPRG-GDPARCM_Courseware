#include "BaseRunner.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "HUDScreen.h"
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "SpikePowerup.h"
#include "MainMenuScreen.h"
#include "ApplicationManager.h"
#include "EnemyAirplane.h"

const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(1024, 768), "HO: UI System", sf::Style::Close) {

	ApplicationManager::initialize(&this->window);

	//load textures
	TextureManager::getInstance()->loadAll();

	//instantiate objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	AirplanePlayer* airplane = new AirplanePlayer("AirPlane");
	AirplaneSupport* support_1 = new AirplaneSupport("support_1");
	airplane->attachChild(support_1);
	support_1->setPosition(100, 100);

	AirplaneSupport* support_2 = new AirplaneSupport("support_2");
	airplane->attachChild(support_2);
	support_2->setPosition(-50, 100);

	SpikePowerup* spike_1 = new SpikePowerup("spike_1");
	airplane->attachChild(spike_1);
	spike_1->setPosition(-30, 0);

	SpikePowerup* spike_2 = new SpikePowerup("spike_2");
	airplane->attachChild(spike_2);
	spike_2->setPosition(70, 0);

	GameObjectManager::getInstance()->addObject(airplane);

	//TEST: Create N enemies
	for (int i = 0; i < 50; i++) {
		EnemyAirplane* enemy = new EnemyAirplane(i, "enemy_" + to_string(i));
		GameObjectManager::getInstance()->addObject(enemy);
	}

	HUDScreen* hudScreen = new HUDScreen("HUDScreen");
	GameObjectManager::getInstance()->addObject(hudScreen);

	//MainMenuScreen* menuScreen = new MainMenuScreen("MainMenuScreen");
	//GameObjectManager::getInstance()->addObject(menuScreen);
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		srand(elapsedTime.asMicroseconds());
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
	if (ApplicationManager::getInstance()->isPaused() == false) {
		GameObjectManager::getInstance()->update(elapsedTime);
	}
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}