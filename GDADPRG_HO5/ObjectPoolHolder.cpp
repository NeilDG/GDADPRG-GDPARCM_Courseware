#include "ObjectPoolHolder.h"

string ObjectPoolHolder::ENEMY_POOL_TAG = "EnemyPool";

ObjectPoolHolder* ObjectPoolHolder::sharedInstance = NULL;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new ObjectPoolHolder();
	}

	return sharedInstance;
}

void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->getTag()] = pool;
}

void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->getTag());
}

GameObjectPool* ObjectPoolHolder::getPool(string tag)
{
	return this->poolMap[tag];
}
