#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;
GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
	sharedInstance->init();
}

GameObjectManager::GameObjectManager() {}
GameObjectManager::~GameObjectManager() {}

void GameObjectManager::init()
{
}

void GameObjectManager::update(float deltaTime, RECT viewport)
{
	for (GameObject* obj : this->GOList)
	{
		if (obj->isActive)
			obj->update(deltaTime, viewport);
	}
}

void GameObjectManager::render()
{
	for (GameObject* obj : this->GOList)
		obj->draw();
}

void GameObjectManager::addGameObject(PRIMITIVE type, int count)
{
	for (int i = 0; i < count; i++) {
		switch (type) {
			case QUAD:
			case PULSING_QUAD:
			case AREA51_QUAD:
				this->createQuad(type);
				break;
			case CIRCLE:
			case BOUNCING_CIRCLE:
				this->createCircle(type);
				break;
			case CUBE:
			case ROTATING_CUBE:
				this->createCube(type);
				break;
			case PLANE:
				this->createPlane(type);
				break;
		}
	}
}

void GameObjectManager::removeGameObject(GameObject* go)
{
	std::vector<GameObject*>::iterator it;

	for (it = this->GOList.begin(); it != this->GOList.end(); ++it) {
		if (*it == go)
			this->GOList.erase(it);
	}
}

Quad* GameObjectManager::createQuad(PRIMITIVE type)
{
	//std::cout << "Creating Quad." << std::endl;
	QuadVertices pos = { Vector3(0), Vector3(0), Vector3(0), Vector3(0) };
	QuadColors color1 = { CREAM, MATCHA, SPACE, LAVENDER };
	QuadColors color2 = { LAVENDER, CREAM, MATCHA, SPACE };
	QuadProps quadProps = { pos, pos, color1, color2 };

	Quad* newQuad = new Quad("Quad " + (this->QuadList.size() + 1), quadProps, false);

	switch (type) {
		case PULSING_QUAD:
			free(newQuad);
			newQuad = new PulsingQuad("Pulsing Quad " + (this->QuadList.size() + 1), quadProps, false);
			break;
		case AREA51_QUAD:
			free(newQuad);
			newQuad = new Area51("Test Quad " + (this->QuadList.size() + 1), quadProps, false);
			break;
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newQuad);
	this->QuadList.push_back(newQuad);

	return newQuad;
}

Circle* GameObjectManager::createCircle(PRIMITIVE type)
{
	//std::cout << "Creating Circle." << std::endl;
	CircleProps props = {
		Vector3(0), // Starting pos
		0.1f,		// Radius
		25,			// Segments
		PINK,		// Outer color
		CREAM		// Inner color
	};

	Circle* newCircle = new Circle("Circle " + (this->CircleList.size() + 1), props, true);

	switch (type) {
		case BOUNCING_CIRCLE:
			free(newCircle); 
			newCircle = new BouncingCircle("Bouncing Circle " + (this->CircleList.size() + 1), props, true);
			break;
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newCircle);
	this->CircleList.push_back(newCircle);

	return newCircle;
}

Cube* GameObjectManager::createCube(PRIMITIVE type)
{
	CubeVertex props = {
		Vector3(0),
		CREAM,
		PINK
	};

	Cube* newCube = new Cube("Cube " + (this->CubeList.size() + 1), props, true);

	switch (type) {
		case ROTATING_CUBE:
			//std::cout << "Creating Rotating Cube." << std::endl;
			free(newCube);
			newCube = new RotatingCube("Rotating Cube " + (this->CubeList.size() + 1), props, true);
			break;
		default:
			//std::cout << "Creating Cube." << std::endl;
			break;
	}

	this->GOList.push_back((GameObject*)newCube);
	this->CubeList.push_back(newCube);

	return newCube;
}

Plane* GameObjectManager::createPlane(PRIMITIVE type)
{
	PlaneProps props = {
		Vector3(0),
		CREAM,
		0.1f,
		0.1f
	};

	Plane* newPlane = new Plane("Plane " + (this->PlaneList.size() + 1), props, true);

	switch (type) {
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newPlane);
	this->PlaneList.push_back(newPlane);

	return newPlane;
}
