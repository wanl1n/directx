#pragma once
#include <string>
#include "GameObject.h"
#include "Constants.h"

class Camera : public GameObject
{
	protected:
		Matrix4x4 viewMat;

	public:
		Camera(std::string name, OBJECT_TYPE type);
		~Camera();

		Matrix4x4 getCameraView();
};

