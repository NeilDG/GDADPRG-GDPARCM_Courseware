#include <SFML/Graphics.hpp>
class Entity
{
	public:
		Entity();

		void updateTexture(sf::Texture *texture);
		sf::Sprite* getSprite();

	private:
		sf::Texture *texture;
		sf::Sprite *sprite;
};

