#include <iostream>
#include "Game.h"
#include "StringHelpers.hpp"

const float Introduction::Game::PlayerSpeed = 100.f;
const sf::Time Introduction::Game::TimePerFrame = sf::seconds(1.f / 60.f);

Introduction::Game::Game()
	: mWindow(sf::VideoMode(1024, 768), "SFML Application", sf::Style::Close)
	, mTexture()
	, planeSprite()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, numFrames(0)
	//constructor
{
	if (!mTexture.loadFromFile("Media/Textures/Eagle.png"))
	{
		// Handle loading error
	}

	this->movingDown = false;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingUp = false;
	this->mouseDown = false;
	this->shouldMouseMove = false;
	this->mouseTarget = sf::Vector2f();

	planeSprite.setTexture(mTexture);
	planeSprite.setPosition(100.f, 100.f);

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(35);
}

void Introduction::Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Introduction::Game::processEvents()
{
	sf::Event event;
	if (mWindow.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				handleInputWithKB(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handleInputWithKB(event.key.code, false);
				break;

			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					this->handleInputWithMouse(true, event.mouseButton.x, event.mouseButton.y);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					this->handleInputWithMouse(false, event.mouseButton.x, event.mouseButton.y);
				}
				break;	
		}
	}
}

void Introduction::Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (movingUp)
		movement.y -= PlayerSpeed;
	if (movingDown)
		movement.y += PlayerSpeed;
	if (movingLeft)
		movement.x -= PlayerSpeed;
	if (movingRight)
		movement.x += PlayerSpeed;

	planeSprite.move(movement * elapsedTime.asSeconds());
	this->moveSpriteByMouse(elapsedTime);
}

void Introduction::Game::render()
{
	mWindow.clear();
	mWindow.draw(planeSprite);
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Introduction::Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	numFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(numFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / numFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		numFrames = 0;
	}
}

void Introduction::Game::handleInputWithKB(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		movingUp = isPressed;
	else if (key == sf::Keyboard::S)
		movingDown = isPressed;
	else if (key == sf::Keyboard::A)
		movingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		movingRight = isPressed;
	else if (key == sf::Keyboard::Escape)
		mWindow.close();
}

void Introduction::Game::handleInputWithMouse(bool mousePressed, int x, int y) {
	if (mousePressed && !this->mouseDown) {
		std::cout << "Left button click with coordinate " << x << " and " << y << "\n";
		this->mouseDown = true;
		this->shouldMouseMove = true;
		this->mouseTarget = sf::Vector2f(x, y);
		this->destination = sf::Vector2f(x - this->getCenter().x, y - this->getCenter().y);
	}
	else if (!mousePressed && this->mouseDown) {
		std::cout << "Left button released. \n";
		this->mouseDown = false;
	}
}

void Introduction::Game::moveSpriteByMouse(sf::Time elapsedTime) {
	if (this->shouldMouseMove) {
		this->planeSprite.move(this->destination * elapsedTime.asSeconds());
		float dist = this->getDistance(this->getCenter(), this->mouseTarget);

		std::cout << dist * TimePerFrame.asMilliseconds() << "\n";
		if (dist * TimePerFrame.asMilliseconds() < 60.0f) {
			this->shouldMouseMove = false;
		}
	}
}

float Introduction::Game::getDistance(sf::Vector2f v1, sf::Vector2f v2) {
	return sqrtf(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2));
}

sf::Vector2f Introduction::Game::getCenter() {
	sf::Vector2f center(
		this->planeSprite.getPosition().x + (this->mTexture.getSize().x / 2),
		this->planeSprite.getPosition().y + (this->mTexture.getSize().y / 2));

	return center;
}