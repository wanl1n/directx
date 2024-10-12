#pragma once
#include <iostream>
#include <string>

#include "Windows.h"
#include "Constants.h"
#include "Constant.h"
#include "Vector3.h"
#include "Transform.h"

class GameObject
{
	protected:
		std::string m_name;

		Constant cc;
		Transform transform;

		float deltaPos = 0;
		float deltaScale = 0;
		Vector3 deltaRot = Vector3(0);
		float m_time = 0;

	public:
		GameObject(std::string name);
		~GameObject();

		virtual void update(float deltaTime);
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

