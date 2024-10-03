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
		float m_time = 0;

	public:
		GameObject(std::string name);
		~GameObject();

		virtual void update(float deltaTime);
		virtual bool release() = 0;

		virtual void translate(Vector3 offset);
		virtual void rotate(Vector3 offset);
		virtual void scale(Vector3 offset);

		virtual void resetView();

		virtual void project(int type, RECT viewport);
};

