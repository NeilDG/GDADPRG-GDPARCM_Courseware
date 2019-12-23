#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

TextureManager* TextureManager::sharedInstance = NULL;


TextureManager* TextureManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

void TextureManager::loadAll() {
	sf::Texture *texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bed0000.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0000.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0000.png");
	this->textureMap[Box].push_back(texture);

}

sf::Texture* TextureManager::getTextureAt(TextureManager::AssetType assetType, int index) {
	if (!this->textureMap[assetType].empty()) {
		return this->textureMap[assetType][index];
	}
	else {
		cout << "No texture found for " << assetType;
		return NULL;
	}
}

void TextureManager::testFunction() {
	std::cout << "Texture manager is a singleton!";
}