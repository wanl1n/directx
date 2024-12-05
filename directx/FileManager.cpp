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

void FileManager::saveLevel(std::string filename)
{
	std::cout << "Saving level..." << std::endl;

	std::ofstream mainLevel("Levels/" + filename + ".level");

	// Save all Game Objects.
	for (GameObject* obj : GameObjectManager::getInstance()->getGameObjects()) {
		mainLevel << "{" << std::endl;

		mainLevel << "Game Object" << std::endl;

		mainLevel << obj->getName() << std::endl;
		mainLevel << obj->getTypeString() << std::endl;
		mainLevel << obj->getActive() << std::endl;
		mainLevel << obj->getLocalPosition().x << "," << obj->getLocalPosition().y << "," << obj->getLocalPosition().z << "," << std::endl;
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

void FileManager::loadLevel(std::string filename)
{
	std::cout << "Loading level..." << std::endl;

	std::string fileDirectory = "Levels/" + filename + ".level";
	if (filename.find(".level") != std::string::npos)
	{
		fileDirectory = "Levels/" + filename;
	}

	std::fstream sceneFile;
	sceneFile.open(fileDirectory, std::ios::in);

	std::vector<Object> objects;

	int index = 0;
	std::string line;
	while (std::getline(sceneFile, line))
	{
		if (line == "{")
			std::getline(sceneFile, line);

		if (line == "Game Object") {
			Object newObj;

			std::getline(sceneFile, line);
			std::string name = line;
			newObj.name = name;

			std::getline(sceneFile, line);
			std::string type = line;
			newObj.type = type;

			std::getline(sceneFile, line);
			std::string active = line;
			newObj.active = contains(active, "1") ? true : false;

			std::getline(sceneFile, line);
			std::string position = line;
			newObj.position = readVector3(position);

			std::getline(sceneFile, line);
			std::string scale = line;
			newObj.scale = readVector3(scale);

			std::getline(sceneFile, line);
			std::string rotation = line;
			newObj.rotation = readVector3(rotation);

			std::getline(sceneFile, line);
			if (contains(line, "Rigidbody")) {
				newObj.physics = line;
				std::getline(sceneFile, line);
				newObj.physicsType = line;
				
				std::getline(sceneFile, line);
				if (line == "}")
					objects.push_back(newObj);

			}
			else { // {
				newObj.physics = "";
				newObj.physicsType = "";
				if (line == "}")
					objects.push_back(newObj);
			}
		}
	}

	this->createGameObjectsFromFile(objects);
}

void FileManager::createGameObjectsFromFile(std::vector<Object> objects)
{
	for (Object obj : objects) {
		GameObject* go = GameObjectManager::getInstance()->addGameObject(stringToObjType(obj.type));
		go->setName(obj.name);
		go->setActive(obj.active);
		go->setPosition(obj.position);
		go->setScale(obj.scale);
		go->setRotation(obj.rotation);
		
		// Physics Component
		if (contains(obj.physics, "Rigidbody")) {
			std::cout << obj.name << std::endl;
			PhysicsComponent* rb = new PhysicsComponent(go->getName() + " Rigidbody", go);
			rb->setRBType(obj.physicsType);
			go->attachComponent(rb);
			go->setPhysicsOn(true);
		}
	}
}

bool FileManager::contains(std::string str, std::string substr) {

	std::string lowerStr;
	for (char c : str) {
		lowerStr += tolower(c);
	}

	std::string lowerSubstr;
	for (char c : substr) {
		lowerSubstr += tolower(c);
	}

	if (lowerStr.find(lowerSubstr) != std::string::npos) {
		return true;
	}

	return false;
}

Math::Vector3 FileManager::readVector3(std::string csfloat3)
{
	Math::Vector3 vec3 = Math::Vector3(0);

	std::string temp = "";
	int index = 0;
	for (char i : csfloat3)
	{
		if (i != ',')
			temp += i;
		else if (i == ',')
		{
			if (index == 0)
				vec3.x = std::stof(temp);
			if (index == 1)
				vec3.y = std::stof(temp);
			if (index == 2)
				vec3.z = std::stof(temp);

			index++;
			temp = "";
		}
	}

	return vec3;
}

OBJECT_TYPE FileManager::stringToObjType(std::string type)
{
	if (contains(type, "Cube"))
		return CUBE;
	if (contains(type, "Plane"))
		return PLANE;
	if (contains(type, "Sphere"))
		return SPHERE;
	if (contains(type, "Cylinder"))
		return CYLINDER;
	if (contains(type, "Capsule"))
		return CAPSULE;
}
