#pragma once
#include <iostream>
#include <string>

#include "Windows.h"
#include "Constants.h"
#include "Vertex.h"
#include "Math.h"
#include "Transform.h"
#include "Enums.h"

class GameObjectManager;

class GameObject
{
	protected:
		std::string m_name;
		bool isActive;
		PRIMITIVE type;

		Constant cc;
		Transform transform;

	private:
		friend class GameObjectManager;

	public:
		GameObject(std::string name);
		GameObject(std::string name, PRIMITIVE type);
		~GameObject();

		virtual void update(float deltaTime, RECT viewport);
		virtual void draw();
		virtual bool release() = 0;

		virtual void translate(Vector3 offset, float speed);
		virtual void rotateX(float offset);
		virtual void rotateY(float offset);
		virtual void rotateZ(float offset);
		virtual void scale(Vector3 offset);

		virtual void setPosition(Vector3 newPos);
		virtual void setPosition(float x, float y, float z);

		virtual Vector3 getPosition();

		virtual void resetView();

		virtual void project(int type, RECT viewport);
};

