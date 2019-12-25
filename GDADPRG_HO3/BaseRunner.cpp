#include "BaseRunner.h"

const sf::Time BaseRunner::TimePerFrame = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(1024, 768), "HO: Entity Component", sf::Style::Close) {

}

void BaseRunner::run() {
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

void BaseRunner::processEvents()
{
	
}

void BaseRunner::update(sf::Time elapsedTime) {
	
}

void BaseRunner::render() {
	this->window.clear();

	sf::Texture texture;
	texture.loadFromFile("Media/Textures/Desert.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	texture.setRepeated(true);
	sf::IntRect rect;
	rect.width = 1024; rect.height = 768;
	sprite.setTextureRect(rect);
	this->window.draw(sprite);

	this->window.display();
}