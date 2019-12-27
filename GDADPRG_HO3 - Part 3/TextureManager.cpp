#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

void TextureManager::loadAll() {
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/Eagle.png");
	this->textureMap[Eagle].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/Desert.png");
	texture->setRepeated(true);
	this->textureMap[BG].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/Raptor.png");
	texture->setRepeated(true);
	this->textureMap[Raptor].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/spike.png");
	this->textureMap[Spike].push_back(texture);
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

int TextureManager::getTextureLength(TextureManager::AssetType assetType) {
	if (!this->textureMap[assetType].empty()) {
		return this->textureMap[assetType].size();
	}
	else {
		cout << "No texture found for " << assetType;
		return 0;
	}
}

void TextureManager::testFunction() {
	std::cout << "Texture manager is a singleton!";
}