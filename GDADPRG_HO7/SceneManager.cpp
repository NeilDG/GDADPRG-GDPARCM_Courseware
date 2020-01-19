#include "SceneManager.h"
#include <iostream>

string SceneManager::MAIN_MENU_SCENE_NAME = "MainMenuScene";
string SceneManager::GAME_SCENE_NAME = "GameScene";

SceneManager* SceneManager::sharedInstance = NULL;

using namespace std;
SceneManager* SceneManager::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new SceneManager();
	}

	return sharedInstance;
}

void SceneManager::registerScene(AScene* scene)
{
	std::cout << scene->getSceneName() << " registered! \n";
	this->storedScenes[scene->getSceneName()] = scene;
}

void SceneManager::loadScene(string name)
{
	//put a loading screen!

	this->unloadScene();
	this->activeScene = this->storedScenes[name];
	this->activeScene->onLoadResources();
	this->activeScene->onLoadObjects();
}

void SceneManager::unloadScene()
{
	if (this->activeScene != NULL) {
		this->activeScene->onUnloadObjects();
		this->activeScene->onUnloadResources();
	}
}

bool SceneManager::isSceneLoaded(string name)
{
	return this->activeScene->getSceneName() == name;
}


/*void SceneManager::unloadAllActiveScenes()
{
	SceneList activeList;
	activeList.reserve(this->activeScenes.size());
	for (auto kv : this->activeScenes) {
		activeList.push_back(kv.first);
	}

	for (int i = 0; i < activeList.size(); i++) {
		this->unloadScene(activeList[i]);
	}
}*/