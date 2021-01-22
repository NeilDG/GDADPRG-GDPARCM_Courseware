#include <fstream>
#include <iostream>
#include <filesystem>
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

TextureManager::TextureManager()
{
	this->countStreamingAssets();
}

void TextureManager::loadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String line;

	while(std::getline(stream, line))
	{
		std::vector<String> tokens = StringUtils::split(line, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(line);
		texture->setRepeated(true);
		this->textureMap[assetName].push_back(texture);
		this->allTextureList.push_back(texture);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::loadStreamingAssets()
{	
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		//simulate loading of very large file
		IETThread::sleep(200);

		String path = entry.path().generic_string();
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(path);
		this->textureMap[assetName].push_back(texture);
		this->allTextureList.push_back(texture);
		
		std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
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

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}
