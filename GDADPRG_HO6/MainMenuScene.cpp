#include "MainMenuScene.h"
#include "MainMenuScreen.h"
#include "GameObjectManager.h"
#include <iostream>

MainMenuScene::MainMenuScene(): AScene("MainMenuScene")
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::onLoadResources()
{
	
}

void MainMenuScene::onLoadObjects()
{
	MainMenuScreen* menuScreen = new MainMenuScreen("MainMenuScreen");
	this->registerObject(menuScreen);

	std::cout << "Main menu scene initialized! \n";
}

void MainMenuScene::onUnloadResources()
{

}
