#pragma once
#include <iostream>
#include <string>

#include "Windows.h"
#include "Constants.h"
#include "Vertex.h"
#include "Math.h"
#include "Transform.h"
#include "Constants.h"

class GameObjectManager;

class GameObject
{
	protected:
		std::string name;
		bool isActive;
		OBJECT_TYPE type;

		Constant cc;
		Transform transform;

	private:
		friend class GameObjectManager;

	public:
		GameObject(std::string name);
		GameObject(std::string name, OBJECT_TYPE type);
		~GameObject();

		virtual void update(float deltaTime, RECT viewport);
		virtual void draw();
		virtual bool release() = 0;

		// Transform Functions
		virtual void translate(Vector3 offset, float speed);
		virtual void rotateX(float radians);
		virtual void rotateY(float radians);
		virtual void rotateZ(float radians);
		virtual void scale(Vector3 offset);
		virtual void resetView();
		virtual void project(int type, RECT viewport);

		// Getters/Setters
		virtual void setPosition(Vector3 newPos);
		virtual void setPosition(float x, float y, float z);

		virtual Vector3 getPosition();
		virtual void setRotation(Vector3 newRot);
};

