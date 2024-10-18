#pragma once
#include "vector"
#include "PrimitivesList.h"
#include "Constants.h"

class GameObject;

class GameObjectManager
{
	public:
		static GameObjectManager* getInstance();
		static void initialize();

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

		void init();

	public:
		void update(float deltaTime, RECT viewport);
		void render();

		void addGameObject(OBJECT_TYPE type, int count=1);
		void removeGameObject(GameObject* go);

		void updateCameraView(Matrix4x4 worldCam);
		void setProjection(int type, RECT vp);

	private:
		Quad* createQuad(OBJECT_TYPE type);
		Circle* createCircle(OBJECT_TYPE type);
		Cube* createCube(OBJECT_TYPE type);
		Plane* createPlane(OBJECT_TYPE type);
		Sphere* createSphere(OBJECT_TYPE type);
		Cylinder* createCylinder(OBJECT_TYPE type);
		Capsule* createCapsule(OBJECT_TYPE type);
};

