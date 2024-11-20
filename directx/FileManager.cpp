#include "FileManager.h"

#include "GameObjectManager.h"
#include "PhysicsComponent.h"

FileManager* FileManager::sharedInstance = nullptr;
FileManager* FileManager::getInstance()
{
	return sharedInstance;
}

void FileManager::initialize()
{
	sharedInstance = new FileManager();
	//sharedInstance->init();
}

void FileManager::destroy()
{
	delete sharedInstance;
}

FileManager::FileManager() {}
FileManager::~FileManager() {}

void FileManager::saveLevel()
{
	std::cout << "Saving level..." << std::endl;

	std::ofstream mainLevel("Levels/Main Scene.level");

	// Save all Game Objects.
	for (GameObject* obj : GameObjectManager::getInstance()->getGameObjects()) {
		mainLevel << "{" << std::endl;

		mainLevel << "Game Object" << std::endl;

		mainLevel << obj->getName() << std::endl;
		mainLevel << obj->getTypeString() << std::endl;
		mainLevel << obj->getActive() << std::endl;
		mainLevel << obj->getPosition().x << "," << obj->getPosition().y << "," << obj->getPosition().z << "," << std::endl;
		mainLevel << obj->getScale().x << "," << obj->getScale().y << "," << obj->getScale().z << "," << std::endl;
		mainLevel << obj->getRotation().x << "," << obj->getRotation().y << "," << obj->getRotation().z << "," << std::endl;

		std::vector<Component*> components = obj->getAllComponents();
		for (Component* comp : components) {
			if (comp->getType() == Component::ComponentType::Physics) {
				PhysicsComponent* phyComp = (PhysicsComponent*)comp;

				if (phyComp != NULL) {
					mainLevel << comp->getName() << std::endl;
					mainLevel << phyComp->getRBType() << std::endl;
				}
			}
		}

		mainLevel << "}" << std::endl;
	}

	mainLevel.close();
}