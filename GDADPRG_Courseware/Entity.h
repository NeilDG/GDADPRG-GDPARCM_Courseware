#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Entity
{
	public:
		Entity();

		void updateTexture(sf::Texture *texture, TextureManager::AssetType assetType);
		void incrementTexture();
		sf::Sprite* getSprite();
		TextureManager::AssetType getAssetType();

	private:
		TextureManager::AssetType assetType;
		sf::Texture *texture;
		sf::Sprite *sprite;

		int counter;
};

