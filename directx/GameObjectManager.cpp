#include "GameObjectManager.h"
#include "CameraManager.h"

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
			case LERPING_CUBE:
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
	QuadVertices pos = { Vector3(-sides, -sides, 0), 
						 Vector3(-sides, sides, 0), 
						 Vector3(sides, -sides, 0), 
						 Vector3(sides, sides, 0) };
	QuadColors color1 = { CREAM, MATCHA, SPACE, LAVENDER };
	QuadColors color2 = { LAVENDER, CREAM, MATCHA, SPACE };
	QuadProps quadProps = { pos, pos, color1, color2 };

	Quad* newQuad = new Quad("Quad " + std::to_string(this->QuadList.size() + 1), quadProps, false);

	switch (type) {
		case PULSING_QUAD:
			free(newQuad);
			newQuad = new PulsingQuad("Pulsing Quad " + std::to_string(this->QuadList.size() + 1), quadProps, false);
			break;
		case AREA51_QUAD:
			free(newQuad);
			newQuad = new Area51("Test Quad " + std::to_string(this->QuadList.size() + 1), quadProps, false);
			break;
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newQuad);
	this->QuadList.push_back(newQuad);

	return newQuad;
}

Circle* GameObjectManager::createCircle(OBJECT_TYPE type)
{
	//std::cout << "Creating Circle." << std::endl;
	CircleProps props = {
		Vector3(0), // Starting pos
		0.1f,		// Radius
		25,			// Segments
		PINK,		// Outer color
		CREAM		// Inner color
	};

	Circle* newCircle = new Circle("Circle " + std::to_string(this->CircleList.size() + 1), props, true);

	switch (type) {
		case BOUNCING_CIRCLE:
			free(newCircle); 
			newCircle = new BouncingCircle("Bouncing Circle " + std::to_string(this->CircleList.size() + 1), props, true);
			break;
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newCircle);
	this->CircleList.push_back(newCircle);

	return newCircle;
}

Cube* GameObjectManager::createCube(OBJECT_TYPE type)
{
	Cube* newCube = new Cube("Cube " + std::to_string(this->CubeList.size() + 1), true);

	switch (type) {
		case ROTATING_CUBE:
			//std::cout << "Creating Rotating Cube." << std::endl;
			free(newCube);
			newCube = new RotatingCube("Rotating Cube " + std::to_string(this->CubeList.size() + 1), true);
			break;
		case LERPING_CUBE:
			free(newCube);
			newCube = new LerpingCube("Lerping Cube " + std::to_string(this->CubeList.size() + 1), true);
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
			free(newPlane);
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

	switch (type) {
		default:
			break;
	}

	this->GOList.push_back((GameObject*)newSphere);
	this->SphereList.push_back(newSphere);

	return newSphere;
}

Cylinder* GameObjectManager::createCylinder(OBJECT_TYPE type)
{
	Cylinder* newCylinder = new Cylinder("Cylinder " + std::to_string(this->CylinderList.size() + 1), true);

	switch (type) {
	default:
		break;
	}

	this->GOList.push_back((GameObject*)newCylinder);
	this->CylinderList.push_back(newCylinder);

	return newCylinder;
}

Capsule* GameObjectManager::createCapsule(OBJECT_TYPE type)
{
	Capsule* newCapsule = new Capsule("Capsule " + std::to_string(this->CapsuleList.size() + 1), true);

	switch (type) {
	default:
		break;
	}

	this->GOList.push_back((GameObject*)newCapsule);
	this->CapsuleList.push_back(newCapsule);

	return newCapsule;
}

bool GameObjectManager::pick(Point mousePos, float width, float height)
{
	bool rayHit = false;

	for (GameObject* obj : this->GOList) {
		Primitive* object = (Primitive*)obj;
		if (object != NULL) {
			DirectX::XMMATRIX world, view, proj;

			world = DirectX::XMMatrixSet(
				obj->getWorldMat().mat[0][0], obj->getWorldMat().mat[0][1], obj->getWorldMat().mat[0][2], obj->getWorldMat().mat[0][3],
				obj->getWorldMat().mat[1][0], obj->getWorldMat().mat[1][1], obj->getWorldMat().mat[1][2], obj->getWorldMat().mat[1][3],
				obj->getWorldMat().mat[2][0], obj->getWorldMat().mat[2][1], obj->getWorldMat().mat[2][2], obj->getWorldMat().mat[2][3],
				obj->getWorldMat().mat[3][0], obj->getWorldMat().mat[3][1], obj->getWorldMat().mat[3][2], obj->getWorldMat().mat[3][3]
			);
	
			Constant cc;
			cc.view = CameraManager::getInstance()->getActiveCameraView();
			cc.proj = CameraManager::getInstance()->getActiveProjection();

			view = DirectX::XMMatrixSet(
				cc.view.mat[0][0], cc.view.mat[0][1], cc.view.mat[0][2], cc.view.mat[0][3],
				cc.view.mat[1][0], cc.view.mat[1][1], cc.view.mat[1][2], cc.view.mat[1][3],
				cc.view.mat[2][0], cc.view.mat[2][1], cc.view.mat[2][2], cc.view.mat[2][3],
				cc.view.mat[3][0], cc.view.mat[3][1], cc.view.mat[3][2], cc.view.mat[3][3]
			);
			proj = DirectX::XMMatrixSet(
				cc.proj.mat[0][0], cc.proj.mat[0][1], cc.proj.mat[0][2], cc.proj.mat[0][3],
				cc.proj.mat[1][0], cc.proj.mat[1][1], cc.proj.mat[1][2], cc.proj.mat[1][3],
				cc.proj.mat[2][0], cc.proj.mat[2][1], cc.proj.mat[2][2], cc.proj.mat[2][3],
				cc.proj.mat[3][0], cc.proj.mat[3][1], cc.proj.mat[3][2], cc.proj.mat[3][3]
			);

			DirectX::XMVECTOR roScreen, rdScreen;
			DirectX::XMVECTOR ro, rd;
			roScreen = DirectX::XMVectorSet(mousePos.x, mousePos.y, 0.1f, 1.0f);
			rdScreen = DirectX::XMVectorSet(mousePos.x, mousePos.y, 1.0f, 1.0f);

			ro = DirectX::XMVector3Unproject(roScreen, 0, 0, width, height, 0, 1, proj, view, world);
			rd = DirectX::XMVector3Unproject(rdScreen, 0, 0, width, height, 0, 1, proj, view, world);
			rd = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(rd, ro));

			DirectX::SimpleMath::Ray ray(ro, rd);

			DirectX::BoundingBox bounds = object->getBounds();

			float dist;
			rayHit = ray.Intersects(bounds, dist);

			GameObjectManager::getInstance()->resetSelection();
			if (rayHit)
			{
				object->setSelected(true);

				DirectX::XMVECTOR hitPoint = DirectX::XMVectorAdd(ro, DirectX::XMVectorScale(rd, dist));

				DirectX::XMFLOAT3 hitPosition;
				DirectX::XMStoreFloat3(&hitPosition, hitPoint);

				object->transform.position = Vector3(hitPosition.x, hitPosition.y, obj->getPosition().z);

				break;
			}
		}
	}


	return rayHit;
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

GameObject* GameObjectManager::checkCollision(Vector3 rayEndPoint)
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
