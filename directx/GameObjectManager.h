#pragma once
#include <d3d11.h>
#include "DirectXMath.h"
#include "SimpleMath/SimpleMath.h"

#include "vector"
#include "PrimitivesList.h"
#include "Constants.h"
#include "Math.h"

#include "MeshObject.h"
#include "SkyboxMeshObject.h"

class GameObject;

class GameObjectManager
{
	public:
		static GameObjectManager* getInstance();
		static void initialize();
		static void destroy();

	private:
		std::vector<GameObject*> GOList;
		std::vector<Quad*> QuadList;
		std::vector<Circle*> CircleList;
		std::vector<Cube*> CubeList;
		std::vector<Plane*> PlaneList;
		std::vector<Sphere*> SphereList;
		std::vector<Cylinder*> CylinderList;
		std::vector<Capsule*> CapsuleList;

	private:
		GameObjectManager();
		~GameObjectManager();
		GameObjectManager(GameObjectManager const&) {};
		GameObjectManager& operator = (GameObjectManager const&) {};
		static GameObjectManager* sharedInstance;

	public:
		void update(float deltaTime, RECT viewport);
		void render();

		void addGameObject(OBJECT_TYPE type, int count=1);
		void removeGameObject(GameObject* go);

		void updateCameraView(Matrix4x4 worldCam);
		void setProjection(Matrix4x4 projMat);

	private:
		Quad* createQuad(OBJECT_TYPE type);
		Circle* createCircle(OBJECT_TYPE type);
		Cube* createCube(OBJECT_TYPE type);
		Plane* createPlane(OBJECT_TYPE type);
		Sphere* createSphere(OBJECT_TYPE type);
		Cylinder* createCylinder(OBJECT_TYPE type);
		Capsule* createCapsule(OBJECT_TYPE type);
		MeshObject* createMesh(OBJECT_TYPE type);

	public:
		DirectX::XMVECTOR pick(Math::Vector2 mousePos, float width, float height);
		void transformSelectedGameObject(DirectX::XMVECTOR deltaHitPoint);
		GameObject* findGameObject(std::string name);
		GameObject* getGameObject(int index);
		GameObject* getSelectedGameObject();
		std::vector<GameObject*> getGameObjects();
		GameObject* checkCollision(Math::Vector3 rayEndPoint);
		void setSelectedGameObject(GameObject* obj);
		void resetSelection();
};

