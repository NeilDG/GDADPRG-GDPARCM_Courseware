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
	this->textureMap[UI_BG].push_back(texture);

	texture = new sf::Texture();
	texture->loadFromFile("Media/Textures/bar_1.png");
	this->textureMap[HUD_BG].push_back(texture);

	sf::Font* font = new sf::Font();
	if (font->loadFromFile("Media/Sansation.ttf")) {
		std::cout << "Font loaded successfully! \n";
		this->fontMap[DefaultFont] = font;
	}

	texture = new sf::Texture();
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

sf::Font* TextureManager::getFont(FontType fontType)
{
	return this->fontMap[fontType];
}

void TextureManager::testFunction() {
	std::cout << "Texture manager is a singleton!";
}