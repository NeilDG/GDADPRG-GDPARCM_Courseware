#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>

namespace Introduction {
	class Game : private sf::NonCopyable
	{
	public:
		Game();
		void					run();


	private:
		void					processEvents();
		void					update(sf::Time elapsedTime);
		void					render();

		void					updateStatistics(sf::Time elapsedTime);
		void					handleInputWithKB(sf::Keyboard::Key key, bool isPressed);

		void handleInputWithMouse(bool mousePressed, int x, int y);

		void moveSpriteByMouse(sf::Time elapsedTime);

		float getDistance(sf::Vector2f v1, sf::Vector2f v2);

		sf::Vector2f getCenter();


	private:
		static const float		PlayerSpeed;
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		sf::Texture				mTexture;
		sf::Sprite				planeSprite;
		sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;

		unsigned int			numFrames;
		bool					movingUp;
		bool					movingDown;
		bool					movingRight;
		bool					movingLeft;
		bool mouseDown;
		bool shouldMouseMove;
		sf::Vector2f mouseTarget;
		sf::Vector2f destination;
	};

#endif // BOOK_GAME_HPP
}