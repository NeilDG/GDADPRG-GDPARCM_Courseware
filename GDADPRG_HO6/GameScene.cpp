#include "GameScene.h"
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "SpikePowerup.h"
#include "EnemyAirplane.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EmptyGameObject.h"
#include "EnemySwarmHandler.h"
#include "HUDScreen.h"

GameScene::GameScene():AScene("GameScene")
{

}

GameScene::~GameScene()
{
}

void GameScene::onLoadResources()
{
}

void GameScene::onLoadObjects()
{
	//instantiate objects
	BGObject* bgObject = new BGObject("BGObject");
	this->registerObject(bgObject);

	AirplanePlayer* airplane = new AirplanePlayer("AirPlane");
	AirplaneSupport* support_1 = new AirplaneSupport("support_1");
	airplane->attachChild(support_1);
	support_1->setPosition(100, 100);

	AirplaneSupport* support_2 = new AirplaneSupport("support_2");
	airplane->attachChild(support_2);
	support_2->setPosition(-50, 100);

	SpikePowerup* spike_1 = new SpikePowerup("spike_1");
	airplane->attachChild(spike_1);
	spike_1->setPosition(-30, 0);

	SpikePowerup* spike_2 = new SpikePowerup("spike_2");
	airplane->attachChild(spike_2);
	spike_2->setPosition(70, 0);

	this->registerObject(airplane);

	//create N enemies via object pooling
	srand(time(NULL));
	EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
	EnemySwarmHandler* swarmHandler = new EnemySwarmHandler(10, "SwarmHandler");
	enemiesManager->attachComponent(swarmHandler);
	this->registerObject(enemiesManager);

	HUDScreen* hudScreen = new HUDScreen("HUDScreen");
	this->registerObject(hudScreen);
}

void GameScene::onUnloadObjects()
{
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(enemyPool);
	AScene::onUnloadObjects();
}

void GameScene::onUnloadResources()
{
}
