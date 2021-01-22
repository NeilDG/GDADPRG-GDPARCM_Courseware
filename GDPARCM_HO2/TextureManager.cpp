#include <fstream>
#include <iostream>
#include "TextureManager.h"
#include "StringUtils.h"
#include "IETThread.h"

//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

void TextureManager::loadFromAssetList()
{
	std::cout << "Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String line;

	while(std::getline(stream, line))
	{
		std::vector<String> tokens = StringUtils::split(line, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

		//simulate loading of very large file
		IETThread::sleep(2000);
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(line);
		texture->setRepeated(true);
		this->textureMap[assetName].push_back(texture);
		this->allTextureList.push_back(texture);
		std::cout << "Loaded texture: " << assetName << std::endl;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		std::cout << "No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		std::cout << "No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getTextureFromList(const int index)
{
	return this->allTextureList[index];
}

int TextureManager::getNumLoadedTextures() const
{
	return this->allTextureList.size();
}
