#pragma once
#include <string>
#include "Windows.h"
#include "GameObject.h"
#include "InputListener.h"
#include "Constants.h"

class CameraManager;

class Camera : public GameObject, public InputListener
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

		// Inherited from InputListener.
		void onKeyDown(int key) override;
		void onKeyUp(int key) override;
		void onMouseMove(const Point& mousePos) override;
		void onLeftMouseDown(const Point& mousePos) override;
		void onRightMouseDown(const Point& mousePos) override;
		void onLeftMouseUp(const Point& mousePos) override;
		void onRightMouseUp(const Point& mousePos) override;
};

