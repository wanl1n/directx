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

		int type = 0;
		float forward = 0;
		float rightward = 0;
		float panSpeed = 0.1f;
		float moveSpeed = 0.3f;

		bool moving = false;
		RECT viewport;

		GameObject* lastSelectedGO;

		friend class CameraManager;

	public:
		Camera(std::string name, RECT viewport, OBJECT_TYPE type = CAMERA);
		~Camera();

		virtual void update();
		virtual void checkForInput();
		virtual void updateViewMatrix();
		virtual void updateProjectionMatrix();

		float getPanSpeed();
		Matrix4x4 getViewMatrix();
		Matrix4x4 getProjMatrix();
		void setForward(float dir);
		void setRightward(float dir);
		void setProjectionType(int type);

		// Inherited from InputListener.
		void onMouseMove(const Point& mousePos) override;
		void onLeftMouseDown(const Point& mousePos) override;
		void onRightMouseDown(const Point& mousePos) override;
		void onLeftMouseUp(const Point& mousePos) override;
		void onRightMouseUp(const Point& mousePos) override;
};

