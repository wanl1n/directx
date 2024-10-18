#pragma once
#include <string>
#include "GameObject.h"
#include "Constants.h"

class CameraManager;

class Camera : public GameObject
{
	protected:
		Matrix4x4 prevCamMat;
		Matrix4x4 viewMat;
		int type = 0;
		float forward = 0;
		float rightward = 0;
		float panSpeed = 0.1f;

		friend class CameraManager;

	public:
		Camera(std::string name, OBJECT_TYPE type = CAMERA);
		~Camera();

		virtual void update(RECT viewport);
		virtual void updateTransform();
		virtual void project(RECT viewport);

		float getPanSpeed();
		Matrix4x4 getCameraView();
		Matrix4x4 getProjMatrix();
		void setForward(float dir);
		void setRightward(float dir);
};

