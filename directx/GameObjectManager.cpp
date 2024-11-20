#include "GameObjectManager.h"
#include "CameraManager.h"
#include "EngineTime.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;
GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	if (sharedInstance == NULL)
		return;
	delete sharedInstance;
}

GameObjectManager::GameObjectManager() {}

GameObjectManager::~GameObjectManager() 
{
	this->GOList.clear();
	this->QuadList.clear();
	this->CircleList.clear();
	this->CubeList.clear();
	this->PlaneList.clear();
	this->SphereList.clear();
	this->CylinderList.clear();
	this->CapsuleList.clear();
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
	{
		if (obj->isActive)
			obj->draw();
	}
}

void GameObjectManager::addGameObject(OBJECT_TYPE type, int count)
{
	for (int i = 0; i < count; i++) {
		switch (type) {
			case QUAD:
				this->createQuad(type);
				break;
			case CIRCLE:
				this->createCircle(type);
				break;
			case CUBE:
			case PHYSICS_CUBE:
			case PHYSICS_PLANE:
				this->createCube(type);
				break;
			case PLANE:
			case ROTATING_PLANE:
				this->createPlane(type);
				break;
			case SPHERE:
				this->createSphere(type);
				break;
			case CYLINDER:
				this->createCylinder(type);
				break;
			case CAPSULE:
				this->createCapsule(type);
				break;
			case MESH_TEAPOT:
			case MESH_BUNNY:
			case MESH_ARMADILLO:
			case MESH_STATUE:
			case MESH_SUZANNE:
			case MESH_SKY:
				this->createMesh(type);
				break;
			default:
				break;
		}
	}
}

void GameObjectManager::removeGameObject(GameObject* go)
{
	for (int i = 0; i < this->GOList.size(); i++) {
		if (this->GOList[i] == go)
			this->GOList.erase(GOList.begin() + i);
	}
}

void GameObjectManager::updateCameraView(Matrix4x4 worldCam)
{
	for (GameObject* obj : this->GOList)
		obj->cc.view = worldCam;
}

void GameObjectManager::setProjection(Matrix4x4 projMat)
{
	for (GameObject* obj : this->GOList)
		obj->cc.proj = projMat;
}

Quad* GameObjectManager::createQuad(OBJECT_TYPE type)
{
	//std::cout << "Creating Quad." << std::endl;
	float sides = 0.1f;
	QuadVertices pos = { Math::Vector3(-sides, -sides, 0), 
						 Math::Vector3(-sides, sides, 0), 
						 Math::Vector3(sides, -sides, 0), 
						 Math::Vector3(sides, sides, 0) };
	QuadColors color1 = { CREAM, MATCHA, SPACE, LAVENDER };
	QuadColors color2 = { LAVENDER, CREAM, MATCHA, SPACE };
	QuadProps quadProps = { pos, pos, color1, color2 };

	Quad* newQuad = new Quad("Quad " + std::to_string(this->QuadList.size() + 1), quadProps, false);

	this->GOList.push_back((GameObject*)newQuad);
	this->QuadList.push_back(newQuad);

	return newQuad;
}

Circle* GameObjectManager::createCircle(OBJECT_TYPE type)
{
	//std::cout << "Creating Circle." << std::endl;
	CircleProps props = {
		Math::Vector3(0), // Starting pos
		0.1f,		// Radius
		25,			// Segments
		PINK,		// Outer color
		CREAM		// Inner color
	};

	Circle* newCircle = new Circle("Circle " + std::to_string(this->CircleList.size() + 1), props, true);

	this->GOList.push_back((GameObject*)newCircle);
	this->CircleList.push_back(newCircle);

	return newCircle;
}

Cube* GameObjectManager::createCube(OBJECT_TYPE type)
{
	Cube* newCube = new Cube("Cube " + std::to_string(this->CubeList.size() + 1), true);

	switch (type) {
		case PHYSICS_CUBE:
			//std::cout << "Creating Rotating Cube." << std::endl;
			free(newCube);
			newCube = new PhysicsCube("Physics Cube " + std::to_string(this->CubeList.size() + 1), true);
			break;
		case PHYSICS_PLANE:
			free(newCube);
			newCube = new PhysicsPlane("Physics Plane " + std::to_string(this->CubeList.size() + 1), true);
			break;
		default:
			//std::cout << "Creating Cube." << std::endl;
			break;
	}

	this->GOList.push_back((GameObject*)newCube);
	this->CubeList.push_back(newCube);

	return newCube;
}

Plane* GameObjectManager::createPlane(OBJECT_TYPE type)
{
	Plane* newPlane = new Plane("Plane " + std::to_string(this->PlaneList.size() + 1), true);

	switch (type) {
		case ROTATING_PLANE:
			delete newPlane;
			newPlane = new RotatingPlane("Rotating Plane " + std::to_string(this->PlaneList.size() + 1), true);
			break;
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newPlane);
	this->PlaneList.push_back(newPlane);

	return newPlane;
}

Sphere* GameObjectManager::createSphere(OBJECT_TYPE type)
{
	Sphere* newSphere = new Sphere("Sphere " + std::to_string(this->SphereList.size() + 1), true);

	/*switch (type) {
		default:
			break;
	}*/

	this->GOList.push_back((GameObject*)newSphere);
	this->SphereList.push_back(newSphere);

	return newSphere;
}

Cylinder* GameObjectManager::createCylinder(OBJECT_TYPE type)
{
	Cylinder* newCylinder = new Cylinder("Cylinder " + std::to_string(this->CylinderList.size() + 1), true);

	/*switch (type) {
	default:
		break;
	}*/

	this->GOList.push_back((GameObject*)newCylinder);
	this->CylinderList.push_back(newCylinder);

	return newCylinder;
}

Capsule* GameObjectManager::createCapsule(OBJECT_TYPE type)
{
	Capsule* newCapsule = new Capsule("Capsule " + std::to_string(this->CapsuleList.size() + 1), true);

	/*switch (type) {
	default:
		break;
	}*/

	this->GOList.push_back((GameObject*)newCapsule);
	this->CapsuleList.push_back(newCapsule);

	return newCapsule;
}

MeshObject* GameObjectManager::createMesh(OBJECT_TYPE type)
{
	MeshObject* newMesh = new MeshObject(type);

	switch (type) {
		case MESH_SKY:
			free(newMesh);
			newMesh = new SkyboxMeshObject();
			break;
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newMesh);
	return newMesh;
}

void GameObjectManager::transformSelectedGameObject(DirectX::XMVECTOR deltaHitPoint)
{
	GameObject* obj = this->getSelectedGameObject();

	if (obj != NULL) {
		DirectX::XMVECTOR deltaPos = DirectX::XMVector4Normalize(deltaHitPoint);
		float deltaTime = EngineTime::getDeltaTime();

		Math::Vector3 pos = obj->getPosition();
		pos.x += DirectX::XMVectorGetX(deltaPos) * deltaTime;
		pos.y += DirectX::XMVectorGetY(deltaPos) * deltaTime;
		pos.z += DirectX::XMVectorGetZ(deltaPos) * deltaTime;

		obj->setPosition(pos);
	}
}

GameObject* GameObjectManager::findGameObject(std::string name)
{
	for (GameObject* obj : this->GOList) {
		if (obj->name == name)
			return obj;
	}
	return nullptr;
}

GameObject* GameObjectManager::getGameObject(int index)
{
	return this->GOList[index];
}

GameObject* GameObjectManager::getSelectedGameObject()
{
	for (GameObject* obj : this->GOList) {
		if (obj->isSelected)
			return obj;
	}

	return NULL;
}

std::vector<GameObject*> GameObjectManager::getGameObjects()
{
	return this->GOList;
}

GameObject* GameObjectManager::checkCollision(Math::Vector3 rayEndPoint)
{
	for (GameObject* obj : this->GOList) {
		if (obj->isWithinBounds(rayEndPoint))
			return obj;
	}

	return NULL;
}

void GameObjectManager::setSelectedGameObject(GameObject* obj)
{
	for (GameObject* go : this->GOList) {
		go->isSelected = false;
	}

	obj->isSelected = true;
}

void GameObjectManager::resetSelection()
{
	for (GameObject* go : this->GOList) {
		go->isSelected = false;
	}
}
