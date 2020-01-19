#include "ProjectileHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "ProjectileObject.h"
#include "GameObjectManager.h"
#include "AGameObject.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"

ProjectileHandler::ProjectileHandler(int numProjectiles, string name): AComponent(name, Script)
{
	GameObjectPool* projectilePool = new GameObjectPool(ObjectPoolHolder::PROJECT_POOL_TAG, new ProjectileObject("projectile"), 20, NULL);
	projectilePool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(projectilePool);
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::perform()
{
	GameObjectPool* projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
	PlayerInputController* inputController = (PlayerInputController*) GameObjectManager::getInstance()->findObjectByName(AirplanePlayer::AIRPLANE_NAME)->findComponentByName(AirplanePlayer::PLAYER_INPUT_COMPONENT);
	
	this->ticks += this->deltaTime.asSeconds(); //to prevent spamming
	if (inputController->hasFired() && this->ticks > this->SPAWN_INTERVAL) {
		this->ticks = 0.0f;
		projectilePool->requestPoolable();
	}
}
