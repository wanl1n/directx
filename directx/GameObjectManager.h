#pragma once
#include "vector"

#include "GameObject.h"

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	static void initialize();

private:
	std::vector<GameObject*> GOList;

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator = (GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;
};

