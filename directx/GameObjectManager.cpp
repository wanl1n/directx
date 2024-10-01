#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;
GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
	//sharedInstance->init();
}

GameObjectManager::GameObjectManager() {}
GameObjectManager::~GameObjectManager() {}