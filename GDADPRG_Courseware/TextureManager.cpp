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
	texture->loadFromFile("Media/Textures/bed0001.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bed0002.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bed0003.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bed0004.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bed0005.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bed0006.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bed0007.png");
	this->textureMap[Bed].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0001.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0002.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0003.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0004.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0005.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0006.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bench0007.png");
	this->textureMap[Bench].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0000.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0001.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0002.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0003.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0004.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0005.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0006.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/boxGift_0007.png");
	this->textureMap[Box].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0000.png");
	this->textureMap[Coin].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0001.png");
	this->textureMap[Coin].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0002.png");
	this->textureMap[Coin].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0003.png");
	this->textureMap[Coin].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0004.png");
	this->textureMap[Coin].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0005.png");
	this->textureMap[Coin].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0006.png");
	this->textureMap[Coin].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/coin0007.png");
	this->textureMap[Coin].push_back(texture);
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