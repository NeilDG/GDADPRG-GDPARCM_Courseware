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
	texture->loadFromFile("Media/Textures/b_4.png");
	this->textureMap[ButtonNormal].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/b_5.png");
	this->textureMap[ButtonPressed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/f.png");
	this->textureMap[BG].push_back(texture);
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