#pragma once
#include "vector"

#include "Circle.h"
#include "BouncingCircle.h"

#include "Quad.h"
#include "PulsingQuad.h"
#include "Area51.h"

#include "Cube.h"
#include "RotatingCube.h"

#include "Plane.h"

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

		void addGameObject(PRIMITIVE type, int count);
		void removeGameObject(GameObject* go);

	private:
		Quad* createQuad(PRIMITIVE type);
		Circle* createCircle(PRIMITIVE type);
		Cube* createCube(PRIMITIVE type);
		Plane* createPlane(PRIMITIVE type);
};

